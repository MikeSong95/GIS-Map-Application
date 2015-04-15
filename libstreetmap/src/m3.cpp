#include <iostream>
#include <sstream>
#include <string>
#include <algorithm> 
#include <vector>
#include "m3.h"
#include "AStarFunctions.h"
#include "m1.h"

using namespace std;

#define ERROR_VALUE 999999999

extern MapDatabase* mapDatabase;

vector<string> suggestionsText1 = {"","","","",""};
vector<string> suggestionsText2 = {"","","","",""};

// Returns a path (route) between the start intersection and the end 
// intersection, if one exists. If no path exists, this routine returns 
// an empty (size == 0) vector. If more than one path exists, the path 
// with the shortest travel time is returned. The path is returned as a vector 
// of street segment ids; traversing these street segments, in the given order,
// would take one from the start to the end intersection.
std::vector<unsigned> find_path_between_intersections(unsigned 
                   intersect_id_start, unsigned intersect_id_end) {
    //mapDatabase->reset_streetEdgeScores();
    setDijkstraDatabase();
    return AStarAlgorithm(intersect_id_start, intersect_id_end);
}

// Returns the time required to travel along the path specified. The path
// is passed in as a vector of street segment ids, and this function can 
// assume the vector either forms a legal path or has size == 0.
// The travel time is the sum of the length/speed-limit of each street 
// segment, plus 15 seconds per turn implied by the path. A turn occurs
// when two consecutive street segments have different street names.
double compute_path_travel_time(const std::vector<unsigned>& path) {
    double travelTime = 0;
    double turnTime;
    // For each segment in path, compute the traversal time, determine if there is
    // a turn, and add to travelTime
    for (unsigned i = 0; i < path.size(); i++) { 
        if (i < path.size()-1) {
            turnTime = addTurnTimeMin(path[i], path[i+1]);
        } else {
            turnTime = 0;
        }
        
        travelTime += find_segment_travel_time(path[i]) + turnTime;
    }
    
    return travelTime;
}
    



// Returns the ID of the closest intersection to a POI
// used as a helper function for find_path_to_point_of_interest function
unsigned find_closest_intersection_from_POI (unsigned desiredPOIid) {
    
    LatLon desiredPOIposition = getPointOfInterestPosition(desiredPOIid);

    // set a reference distance to start comparing with (always start cmp with intersection ID = 0)
    double closestDistance = find_distance_between_two_points(desiredPOIposition, getIntersectionPosition(0));
    unsigned closestIntersectionID = 0; // since we're using ID = 0 as reference (see line above)
    LatLon intersectionPosition;
    
    // start loop at 1 because already used intersection ID = 0 above as reference distance for comparison
    for (unsigned i = 1; i < getNumberOfIntersections(); i++) {
        
        intersectionPosition = getIntersectionPosition(i);
        
        if (find_distance_between_two_points(desiredPOIposition,intersectionPosition) < closestDistance) {
            closestDistance = find_distance_between_two_points(desiredPOIposition,intersectionPosition);
            closestIntersectionID = i;
        } else {
            continue;
        }
    }
        
    return closestIntersectionID;
}


// Returns the shortest travel time path (vector of street segments) from 
// the start intersection to a point of interest with the specified name.
// If no such path exists, returns an empty (size == 0) vector.
std::vector<unsigned> find_path_to_point_of_interest (unsigned intersect_id_start, std::string desired_point_of_interest_name) {
  
    vector<unsigned> failure = {ERROR_VALUE};
    vector<unsigned> shortestPathToPOI;
    vector< vector<StreetEdge>>  POIidsWithSameName;
    POIidsWithSameName.resize(2);
    POIidsWithSameName[0].resize(1);
    POIidsWithSameName[1].resize(1);
    POIidsWithSameName[0][0].setPoiID(ERROR_VALUE);
    POIidsWithSameName[0][0].setTravel(ERROR_VALUE);
    POIidsWithSameName[1][0].setPoiID(ERROR_VALUE);
    POIidsWithSameName[1][0].setTravel(ERROR_VALUE);
    
    string POInameToCheckIfMatch;
    double distanceFromStart;
   
    bool foundMatch = false; 
    
    // need to check to see if POI name exists
    if (intersect_id_start != ERROR_VALUE) {
        // Find the two geographically closest POIs, then find their closest intersections and
        // compute + compare their travel times

        // store the closest 2 POI IDs that have the same name as the desired POI destination the user wants
        for (unsigned i = 0; i < getNumberOfPointsOfInterest(); i++) {

            POInameToCheckIfMatch = getPointOfInterestName(i);

            if (POInameToCheckIfMatch == desired_point_of_interest_name) {
                
                foundMatch = true;

                distanceFromStart = find_distance_between_two_points(getPointOfInterestPosition(i), getIntersectionPosition(intersect_id_start));

                if (distanceFromStart < POIidsWithSameName[0][0].getEdgeWeight() && distanceFromStart < POIidsWithSameName[1][0].getEdgeWeight()){

                       POIidsWithSameName[1][0].setTravel(POIidsWithSameName[0][0].getEdgeWeight());
                       POIidsWithSameName[1][0].setPoiID(POIidsWithSameName[0][0].getTargetIntersection());

                       POIidsWithSameName[0][0].setTravel(distanceFromStart);  
                       POIidsWithSameName[0][0].setPoiID(i);

               }else if (distanceFromStart < POIidsWithSameName[1][0].getEdgeWeight()){

                       POIidsWithSameName[1][0].setTravel(distanceFromStart);  
                       POIidsWithSameName[1][0].setPoiID(i);

               }
            } 
        }
        // Potentially have vector of geographically closest two POIs

        if (foundMatch){
            unsigned closestIntersectionIDfromPOI = find_closest_intersection_from_POI(POIidsWithSameName[0][0].getTargetIntersection()); 

            vector<unsigned> IntersectStartToDesiredPOIpath = find_path_between_intersections(intersect_id_start, closestIntersectionIDfromPOI);

            double shortestPathTravelTime = compute_path_travel_time(IntersectStartToDesiredPOIpath);

            shortestPathToPOI = IntersectStartToDesiredPOIpath;

            // Only compare if it has changed from error value 
            // Also, only compute both travel times if their distance from the POI is within 20 km difference
            if (POIidsWithSameName[1][0].getTargetIntersection() != ERROR_VALUE && (POIidsWithSameName[1][0].getEdgeWeight() - POIidsWithSameName[0][0].getEdgeWeight()) < 20){

                closestIntersectionIDfromPOI = find_closest_intersection_from_POI(POIidsWithSameName[1][0].getTargetIntersection());
                IntersectStartToDesiredPOIpath = find_path_between_intersections(intersect_id_start, closestIntersectionIDfromPOI);
            }

            if (compute_path_travel_time(IntersectStartToDesiredPOIpath) < shortestPathTravelTime) {

                shortestPathToPOI = IntersectStartToDesiredPOIpath;
            } 

            return shortestPathToPOI;
        }else{
            
            return failure;
        }
        
    }else{
        
        return failure;
    
    } 
}


unsigned parse_intersection_name (string intersectionName){

    bool andExists = false;
    unsigned intersectionID = ERROR_VALUE;
    size_t foundName;
    string modifiedName = "";
    
    // Remove any leading or trailing whitespace in the entered name
    remove_whitespace(intersectionName);
    intersectionID = find_intersection_id_from_name(intersectionName);
    
    // Handle case of empty user input 
    if (intersectionName == ""){
        intersectionID = ERROR_VALUE;
        return intersectionID;
    }
    
    istringstream StringStream(intersectionName);
    string word;

    if (intersectionID == ERROR_VALUE){
        
         // Capitalize all first letters 
         while(StringStream >> word) {
             if (word == "&")
                 ; // don't change word
             else if (word == "+")
                 ; // don't change word 
             else if (word[0] > 90)
                 word[0] = word[0] - 32;
        
             modifiedName = modifiedName + word + " ";
        }
        
        // See if it was a capitalization issue or an internal whitespace issue
        remove_whitespace(modifiedName);
        intersectionID = find_intersection_id_from_name(modifiedName);
        
        if (intersectionID == ERROR_VALUE){
        //--------------------Check error with & -----------------------//
        
            for (unsigned i = 0; i < 10; i++){
                if (modifiedName.find(" and ", 0) != std::string::npos){
                    foundName = modifiedName.find(" and ");
                    modifiedName.replace(foundName, std::string(" and ").length(), " & ");
                }else if (modifiedName.find(" AND ", 0) != std::string::npos){
                    foundName = modifiedName.find(" AND ");
                    modifiedName.replace(foundName, std::string(" AND ").length(), " & ");
                }else if (modifiedName.find(" And ", 0) != std::string::npos){
                    foundName = modifiedName.find(" And ");
                    modifiedName.replace(foundName, std::string(" And ").length(), " & ");
                }else if (modifiedName.find(" aNd ", 0) != std::string::npos){
                    foundName = modifiedName.find(" aNd ");
                    modifiedName.replace(foundName, std::string(" aNd ").length(), " & ");
                }else if (modifiedName.find(" anD ", 0) != std::string::npos){
                    foundName = modifiedName.find(" anD ");
                    modifiedName.replace(foundName, std::string(" anD ").length(), " & ");
                }else if (modifiedName.find(" ANd ", 0) != std::string::npos){
                    foundName = modifiedName.find(" ANd ");
                    modifiedName.replace(foundName, std::string(" ANd ").length(), " & ");
                }else if (modifiedName.find(" aND ", 0) != std::string::npos){
                    foundName = modifiedName.find(" aND ");
                    modifiedName.replace(foundName, std::string(" aND ").length(), " & ");
                }else if (modifiedName.find(" AnD ", 0) != std::string::npos){
                    foundName = modifiedName.find(" AnD ");
                    modifiedName.replace(foundName, std::string(" AnD ").length(), " & ");
                }else if (modifiedName.find(" + ", 0) != std::string::npos){
                    foundName = modifiedName.find(" + ");
                    modifiedName.replace(foundName, std::string(" + ").length(), " & ");
                }
            }
            // See if & was in fact the issue 
            remove_whitespace(modifiedName);
            intersectionID = find_intersection_id_from_name(modifiedName);
        
            if (intersectionID == ERROR_VALUE){
                
                // First check to see if & is in the string
                if (modifiedName.find(" & ", 0) != std::string::npos){
                    andExists = true;
                    intersectionID = lazy_user_input(modifiedName);  
                }
                
                if (intersectionID == ERROR_VALUE){
                    string firstStreet = "";
                    string secondStreet = "";
                    bool reachedAnd = false;

                    // There is no &, just return error intersection ID
                    if (!andExists){
                        intersectionID = ERROR_VALUE;
                        return intersectionID;
                    }

                    // Then check to see if it was an order issue
                    istringstream StringStream2(modifiedName);

                    while(StringStream2 >> word && andExists) {

                        if (word == "&")
                            reachedAnd = true;
                        else if(!reachedAnd)
                            firstStreet = firstStreet + word + " ";
                        else
                            secondStreet = secondStreet + word + " ";

                    }

                    firstStreet.erase(firstStreet.end() - 1);
                    secondStreet.erase(secondStreet.end() - 1);
                    modifiedName = secondStreet + " & " + firstStreet;
                    remove_whitespace(modifiedName);
                    intersectionID = find_intersection_id_from_name(modifiedName);

                } // end of parsing street order
            } // end of lazy user input 
        }  // end of parsing & case
    } // end of parsing capitalization error
 
    return intersectionID;
    
}

// Removes leading and trailing whitespace from intersection name =
void remove_whitespace(string& intersectionName){
    
      size_t whiteString = intersectionName.find_first_not_of(" \t");
      intersectionName.erase(0, whiteString);
   
      whiteString = intersectionName.find_last_not_of(" \t");
      if (string::npos != whiteString)
         intersectionName.erase(whiteString+1);
}

vector<string> predictive_streets(string currentText, unsigned textNum){

    if (currentText.size() >= 1 && currentText[currentText.size() - 1] == '|')
        currentText.erase(currentText.end() - 1);
    
    string readIn = "";
    
    istringstream StringStream(currentText);
    string word;
        
    // Capitalize all first letters 
    while(StringStream >> word) {
        if (word == "&")
            ; // don't change word
        else if (word == "+")
            ; // don't change word 
        else if (word[0] > 90)
            word[0] = word[0] - 32;

        readIn = readIn + word + " ";
    }
    
    currentText = readIn;
 
    string streetName;
    unsigned currentTextSize = currentText.size();
    unsigned streetNamesize = 0;
    unsigned similarityCount = 0;
    
    // Don't suggest text for string with less than 3 characters
    if (currentText.length() < 4 && textNum == 1)
        return suggestionsText1; 
    else if (currentText.length() < 4 && textNum == 2)
        return suggestionsText2;

    for (unsigned streetID = 0; streetID < getNumberOfStreets(); streetID++){
        
        streetName = getStreetName(streetID);
        streetNamesize = streetName.size();
         
        for(unsigned i = 0; i < min(streetNamesize,currentTextSize); i++){
            
            if (streetName[i] == currentText[i])
                similarityCount++;
        }
        
        if (similarityCount >= min(streetNamesize,currentTextSize) - 1){
            
            if (textNum == 1){
                if(suggestionsText1.size() >= 5 && (streetName == suggestionsText1[0] || streetName == suggestionsText1[1] || streetName == suggestionsText1[2] || streetName == suggestionsText1[3] || streetName == suggestionsText1[4])){
                    ; 
                }else    
                    suggestionsText1.insert(suggestionsText1.begin(), streetName);
            }else {
                if(suggestionsText2.size() >= 5 && (streetName == suggestionsText2[0] || streetName == suggestionsText2[1] || streetName == suggestionsText2[2] || streetName == suggestionsText2[3] || streetName == suggestionsText2[4])){
                    ; 
                }else    
                    suggestionsText2.insert(suggestionsText2.begin(), streetName);
            }
        }
        
        similarityCount = 0;
    }
    
    if (textNum == 1)
        return suggestionsText1; 
    else
        return suggestionsText2;

}

bool contains_and(string currentText){
    if (currentText.find(" and ", 0) != std::string::npos){
        return true;
    }else if (currentText.find(" AND ", 0) != std::string::npos){
       return true;
    }else if (currentText.find(" And ", 0) != std::string::npos){
        return true;
    }else if (currentText.find(" aNd ", 0) != std::string::npos){
        return true;
    }else if (currentText.find(" anD ", 0) != std::string::npos){
        return true;
    }else if (currentText.find(" ANd ", 0) != std::string::npos){
        return true;
    }else if (currentText.find(" aND ", 0) != std::string::npos){
        return true;
    }else if (currentText.find(" AnD ", 0) != std::string::npos){
        return true;
    }else if (currentText.find(" + ", 0) != std::string::npos){
        return true;
    }else if (currentText.find(" & ", 0) != std::string::npos){
        return true;
    }else
        return false;
}

vector<string> predictive_intersections(string currentText, unsigned textNum){

    size_t foundName;
    
    if (currentText.size() >= 1 && currentText[currentText.size() - 1] == '|')
        currentText.erase(currentText.end() - 1);

    for (unsigned i = 0; i < 10; i++){
        if (currentText.find(" and ", 0) != std::string::npos){
            foundName = currentText.find(" and ");
            currentText.replace(foundName, std::string(" and ").length(), " & ");
        }else if (currentText.find(" AND ", 0) != std::string::npos){
            foundName = currentText.find(" AND ");
            currentText.replace(foundName, std::string(" AND ").length(), " & ");
        }else if (currentText.find(" And ", 0) != std::string::npos){
            foundName = currentText.find(" And ");
            currentText.replace(foundName, std::string(" And ").length(), " & ");
        }else if (currentText.find(" aNd ", 0) != std::string::npos){
            foundName = currentText.find(" aNd ");
            currentText.replace(foundName, std::string(" aNd ").length(), " & ");
        }else if (currentText.find(" anD ", 0) != std::string::npos){
            foundName = currentText.find(" anD ");
            currentText.replace(foundName, std::string(" anD ").length(), " & ");
        }else if (currentText.find(" ANd ", 0) != std::string::npos){
            foundName = currentText.find(" ANd ");
            currentText.replace(foundName, std::string(" ANd ").length(), " & ");
        }else if (currentText.find(" aND ", 0) != std::string::npos){
            foundName = currentText.find(" aND ");
            currentText.replace(foundName, std::string(" aND ").length(), " & ");
        }else if (currentText.find(" AnD ", 0) != std::string::npos){
            foundName = currentText.find(" AnD ");
            currentText.replace(foundName, std::string(" AnD ").length(), " & ");
        }else if (currentText.find(" + ", 0) != std::string::npos){
            foundName = currentText.find(" + ");
            currentText.replace(foundName, std::string(" + ").length(), " & ");
        }
    }
    
    istringstream StringStream(currentText);
    string word;
    string readIn = "";
    
    // Capitalize all first letters 
    while(StringStream >> word) {
        if (word == "&")
            ; // don't change word
        else if (word[0] > 90)
            word[0] = word[0] - 32;

        readIn = readIn + word + " ";
    }
    
    currentText = readIn;
    readIn = "";
    istringstream LineStream(currentText);
    bool findAnd = false;
    string afterAND = "";
    
    // Make vector of words contained before AND, then after AND
    while(LineStream >> word) {
        if (word == "&"){
            findAnd = true;
        }else if (!findAnd){
            readIn = readIn + word + " ";
        }else {
              afterAND = afterAND + word + " ";
        }  
    }
    
    remove_whitespace(readIn);
    remove_whitespace(afterAND);
    currentText = readIn;

    string intersectionName;
    unsigned howManyIN = 0;
    
    // Now I have vector of street names, see if all the names are in the 
    for (unsigned intersectionID = 0; intersectionID < getNumberOfIntersections(); intersectionID++){
        
        intersectionName = getIntersectionName(intersectionID);

        if (intersectionName.find(currentText, 0) != std::string::npos){
            
            if (howManyIN == 0){
                if (textNum == 1){
                    
                    if(suggestionsText1.size() >= 5 && (intersectionName == suggestionsText1[0] || intersectionName == suggestionsText1[1] || intersectionName == suggestionsText1[2] || intersectionName == suggestionsText1[3] || intersectionName == suggestionsText1[4])){
                        ; 
                    }else    
                        suggestionsText1.insert(suggestionsText1.begin(), intersectionName);
                    
                }else{
                    
                    if(suggestionsText2.size() >= 5 && (intersectionName == suggestionsText2[0] || intersectionName == suggestionsText2[1] || intersectionName == suggestionsText2[2] || intersectionName == suggestionsText2[3] || intersectionName == suggestionsText2[4])){
                        ; 
                    }else    
                        suggestionsText2.insert(suggestionsText2.begin(), intersectionName);
                }
            }

            
            if (afterAND.size() >= 1){

                bool foundAND = false;
                string afterANDdatabase = "";
                unsigned similarityCount = 0;
                
                istringstream IntStream(intersectionName);
              
                while(IntStream >> word) {
                   if (word == "&")
                       foundAND = true;
                   else if (foundAND){
                       afterANDdatabase = afterANDdatabase + word + " ";
                   }
                }

                remove_whitespace(afterANDdatabase);

                unsigned intersectionNameNamesize = afterANDdatabase.size();
                unsigned nameSize = afterAND.size();

                for(unsigned i = 0; i < min(intersectionNameNamesize,nameSize); i++){

                    if (afterAND[i] == afterANDdatabase[i])
                        similarityCount++;
                }

                if (similarityCount >= min(intersectionNameNamesize,nameSize) - 1){
                    howManyIN++;
                    
                    if (textNum == 1){

                        if(suggestionsText1.size() >= 5 && (intersectionName == suggestionsText1[0] || intersectionName == suggestionsText1[1] || intersectionName == suggestionsText1[2] || intersectionName == suggestionsText1[3] || intersectionName == suggestionsText1[4])){
                            ; 
                        }else    
                            suggestionsText1.insert(suggestionsText1.begin(), intersectionName);

                    }else{

                        if(suggestionsText2.size() >= 5 && (intersectionName == suggestionsText2[0] || intersectionName == suggestionsText2[1] || intersectionName == suggestionsText2[2] || intersectionName == suggestionsText2[3] || intersectionName == suggestionsText2[4])){
                            ; 
                        }else    
                            suggestionsText2.insert(suggestionsText2.begin(), intersectionName);
                    }
                }

                similarityCount = 0;
             }
        }
    }

    //Return the appropriate vector of intersection suggestions
    if (textNum == 1)
        return suggestionsText1; 
    else
        return suggestionsText2;
}


unsigned lazy_user_input (string currentText){
    
    vector <string> vecWords;
    vector <string> vecIntersections;
     
    size_t foundName;
    
    if (currentText.size() >= 1 && currentText[currentText.size() - 1] == '|')
        currentText.erase(currentText.end() - 1);

    for (unsigned i = 0; i < 10; i++){
        if (currentText.find(" and ", 0) != std::string::npos){
            foundName = currentText.find(" and ");
            currentText.replace(foundName, std::string(" and ").length(), " & ");
        }else if (currentText.find(" AND ", 0) != std::string::npos){
            foundName = currentText.find(" AND ");
            currentText.replace(foundName, std::string(" AND ").length(), " & ");
        }else if (currentText.find(" And ", 0) != std::string::npos){
            foundName = currentText.find(" And ");
            currentText.replace(foundName, std::string(" And ").length(), " & ");
        }else if (currentText.find(" aNd ", 0) != std::string::npos){
            foundName = currentText.find(" aNd ");
            currentText.replace(foundName, std::string(" aNd ").length(), " & ");
        }else if (currentText.find(" anD ", 0) != std::string::npos){
            foundName = currentText.find(" anD ");
            currentText.replace(foundName, std::string(" anD ").length(), " & ");
        }else if (currentText.find(" ANd ", 0) != std::string::npos){
            foundName = currentText.find(" ANd ");
            currentText.replace(foundName, std::string(" ANd ").length(), " & ");
        }else if (currentText.find(" aND ", 0) != std::string::npos){
            foundName = currentText.find(" aND ");
            currentText.replace(foundName, std::string(" aND ").length(), " & ");
        }else if (currentText.find(" AnD ", 0) != std::string::npos){
            foundName = currentText.find(" AnD ");
            currentText.replace(foundName, std::string(" AnD ").length(), " & ");
        }else if (currentText.find(" + ", 0) != std::string::npos){
            foundName = currentText.find(" + ");
            currentText.replace(foundName, std::string(" + ").length(), " & ");
        }
    }
    
    istringstream StringStream(currentText);
    string word;
    string readIn = "";
    
    // Capitalize all first letters 
    while(StringStream >> word) {
        if (word == "&")
            ; // don't change word
        else if (word[0] > 90)
            word[0] = word[0] - 32;

        readIn = readIn + word + " ";
    }
    
    remove_whitespace(readIn);
    currentText = readIn;
    
    istringstream LineStream(currentText);
    
    // Make vector of words
    while(LineStream >> word) {
        if (word == "&")
            ; // don't add to word vector 
        else {
            vecWords.push_back(word);
        }
    }

    bool containsAllWords = true;
    string intersectionName;
    unsigned numWords = vecWords.size();
    for (unsigned intersectionID = 0; intersectionID < getNumberOfIntersections(); intersectionID++){
 
        intersectionName = getIntersectionName(intersectionID);

        for (unsigned i = 0; i < numWords; i++){
            if (intersectionName.find(vecWords[i], 0) != std::string::npos){
                ; // just keep checking
            }else {
                containsAllWords = false; // just keep checking
            }
        }
        
        if(containsAllWords){
            vecIntersections.push_back(intersectionName);
        }
    
       containsAllWords = true; 
    }

    
    if (vecIntersections.size() == 1)
        return find_intersection_id_from_name(vecIntersections[0]);
    else
        return 999999999;
    
}

vector<string> predictive_POIs(string currentText, unsigned textNum){
    
    string capitalInput;
    string lowerCaseInput;
            
    if (currentText.size() >= 1 && currentText[currentText.size() - 1] == '|')
        currentText.erase(currentText.end() - 1);
    
    string readIn = "";
    
    istringstream StringStream(currentText);
    string word;
        
    // Capitalize all first letters 
    while(StringStream >> word) {
        if (word == "&")
            ; // don't change word
        else if (word[0] > 90)
            word[0] = word[0] - 32;

        readIn = readIn + word + " ";
    }
    
    capitalInput = readIn;
    
    istringstream LineStream(currentText);
    readIn = "";
    // Lowercase all first letters 
    while(LineStream >> word) {
        if (word == "&")
            ; // don't change word
        else if (word[0] < 90)
            word[0] = word[0] + 32;

        readIn = readIn + word + " ";
    }
    
    lowerCaseInput = readIn;

    string poiName;
    unsigned lowerCaseTextSize = lowerCaseInput.size();
    unsigned capitalTextSize = capitalInput.size();
    unsigned smallerSize = min(lowerCaseTextSize,capitalTextSize);
    unsigned poiNamesize = 0;
    unsigned similarityCountLow = 0;
    unsigned similarityCountCap = 0;
    
    // Suggest text for POIs after first letter
    if (smallerSize < 2 && textNum == 2){
        if (suggestionsText2.size() >= 5){
            suggestionsText2[0] = "";
            suggestionsText2[1] = "";
            suggestionsText2[2] = "";
            suggestionsText2[3] = "";
            suggestionsText2[4] = "";
        }
       return suggestionsText2;
    }

    for (unsigned poiID = 0; poiID < getNumberOfPointsOfInterest(); poiID++){
        
        poiName = getPointOfInterestName(poiID);
        poiNamesize = poiName.size();
         
        if (poiName != "E" && poiName != "D" && poiName != "C"){    
        
            for(unsigned i = 0; i < min(poiNamesize,lowerCaseTextSize); i++){

                if (poiName[i] == lowerCaseInput[i])
                    similarityCountLow++;
            }

            for(unsigned i = 0; i < min(poiNamesize,capitalTextSize); i++){

                if (poiName[i] == capitalInput[i])
                    similarityCountCap++;
            }

            if (similarityCountLow >= min(poiNamesize,lowerCaseTextSize) - 1){
                if(suggestionsText2.size() >= 5 && (poiName == suggestionsText2[0] || poiName == suggestionsText2[1] || poiName == suggestionsText2[2] || poiName == suggestionsText2[3] || poiName == suggestionsText2[4])){
                    ; 
                }else    
                    suggestionsText2.insert(suggestionsText2.begin(), poiName);
            }
            if (similarityCountCap >= min(poiNamesize,capitalTextSize) - 1){
                if(suggestionsText2.size() >= 5 && (poiName == suggestionsText2[0] || poiName == suggestionsText2[1] || poiName == suggestionsText2[2] || poiName == suggestionsText2[3] || poiName == suggestionsText2[4])){
                    ; 
                }else    
                    suggestionsText2.insert(suggestionsText2.begin(), poiName);
            }
        }
        similarityCountLow = 0;
        similarityCountCap = 0;
    }
    
    return suggestionsText2;

}

void driving_directions(vector <unsigned> path, string start, string destination){
    
    
    unsigned streetID;
    string streetName, previousString;
    unsigned directionCount = 2;
    StreetSegmentEnds currentSegment, lastStreetSegment;
    double currentMaxLon, currentMaxLat, nextMaxLon, nextMaxLat;
    string eastOrWest = "", northOrSouth = "";
    string nextStringLoop;
    unsigned counter = 0;
    
    unsigned currentDir = 0;
    unsigned previousDir = 0;
    bool firstTurn = true; 
    
    cout << endl << "Driving Directions:" << endl << endl;
    cout << "1) Start from "  << start << endl;
    
     
    for(unsigned i = 0; i < path.size(); i++){
        

        streetID = getStreetSegmentStreetID(path[i]);
        streetName = getStreetName(streetID);
        nextStringLoop = streetName;
        currentSegment = getStreetSegmentEnds(path[i]);
        currentMaxLon = max(getIntersectionPosition(currentSegment.from).lon,getIntersectionPosition(currentSegment.to).lon);
        currentMaxLat = max(getIntersectionPosition(currentSegment.from).lat,getIntersectionPosition(currentSegment.to).lat);
        

        // Determine going North or South, and going East or West 
        if (i + 1 < path.size() && streetName != previousString && streetName != "(unknown)"){

            counter = 0;
            while (i+counter < path.size() && streetName == nextStringLoop){
                
                nextStringLoop = getStreetName(getStreetSegmentStreetID(path[i+counter]));
                counter++;  
            }
            
            
            if(i + counter -2 >= 0 && i + counter - 2 < path.size()){
                
                lastStreetSegment = getStreetSegmentEnds(path[i + counter - 2]);
                nextMaxLon = max(getIntersectionPosition(lastStreetSegment.from).lon,getIntersectionPosition(lastStreetSegment.to).lon);
                nextMaxLat = max(getIntersectionPosition(lastStreetSegment.from).lat,getIntersectionPosition(lastStreetSegment.to).lat);
            
            
                if (currentMaxLon > nextMaxLon){
                    eastOrWest = "West";
                    
                }
                else if (currentMaxLon < nextMaxLon){
                    eastOrWest = "East";
                    
                }else{
                    eastOrWest = "Straight";
  
                }

                if (currentMaxLat > nextMaxLat){
                    northOrSouth = " South ";
                    
                }
                else if (currentMaxLat < nextMaxLat){
                    northOrSouth = " North ";
                    
                }
                else{
                    northOrSouth = " Straight ";
                    
                }
            }
        }

        
        if(streetName != previousString && streetName != "(unknown)"){
            
            
            if (northOrSouth == " South "){
                if (eastOrWest == "West"){
                    currentDir = 5;
                }else if (eastOrWest == "East"){
                    currentDir = 7; 
                } else if (eastOrWest == "Straight"){
                    currentDir = 6;
                }
            }else if (northOrSouth == " North "){
                if (eastOrWest == "West"){
                    currentDir = 3;
                }else if (eastOrWest == "East"){
                    currentDir = 1; 
                } else if (eastOrWest == "Straight"){
                    currentDir = 2;
                }
            }else if (northOrSouth == " Straight "){
                if (eastOrWest == "West"){
                    currentDir = 4;
                }else if (eastOrWest == "East"){
                    currentDir = 0; 
                } else {
                    // Don't change anything for straight-straight case
                }
            }
            

            if (!firstTurn){
                if(currentDir == 0){
                    if(previousDir == 0)
                        cout << "Continue to go straight" << endl;
                    else if (previousDir == 1)
                        cout << "Turn Right" << endl;
                    else if (previousDir == 2)
                        cout << "Turn Right" << endl;
                    else if (previousDir == 3)
                        cout << "Turn Right" << endl;
                    else if (previousDir == 4)
                        cout << "Follow road around" << endl;
                    else if (previousDir == 5)
                        cout << "Turn Left" << endl; 
                    else if (previousDir == 6)
                        cout << "Turn Left" << endl; 
                    else if (previousDir == 7)    
                        cout << "Turn Left" << endl; 
                }else if(currentDir == 1){
                    if(previousDir == 0)
                        cout << "Turn Left" << endl; 
                    else if (previousDir == 1)
                        cout << "Continue to go straight" << endl;
                    else if (previousDir == 2)
                        cout << "Turn Right" << endl;
                    else if (previousDir == 3)
                        cout << "Turn Right" << endl;
                    else if (previousDir == 4)
                        cout << "Turn Right" << endl;
                    else if (previousDir == 5)
                        cout << "Follow road around" << endl;
                    else if (previousDir == 6)
                        cout << "Turn Left" << endl; 
                    else if (previousDir == 7)    
                        cout << "Turn Left" << endl; 
                }else if(currentDir == 2){
                    if(previousDir == 0)
                        cout << "Turn Left" << endl; 
                    else if (previousDir == 1)
                        cout << "Turn Left" << endl; 
                    else if (previousDir == 2)
                        cout << "Continue to go straight" << endl;
                    else if (previousDir == 3)
                        cout << "Turn Right" << endl;
                    else if (previousDir == 4)
                        cout << "Turn Right" << endl;
                    else if (previousDir == 5)
                        cout << "Turn Right" << endl;
                    else if (previousDir == 6)
                        cout << "Follow road around" << endl;
                    else if (previousDir == 7)    
                        cout << "Turn Left" << endl; 
                }else if(currentDir == 3){
                    if(previousDir == 0)
                        cout << "Turn Left" << endl; 
                    else if (previousDir == 1)
                        cout << "Turn Left" << endl; 
                    else if (previousDir == 2)
                        cout << "Turn Left" << endl; 
                    else if (previousDir == 3)
                        cout << "Continue to go straight" << endl;
                    else if (previousDir == 4)
                        cout << "Turn Right" << endl;
                    else if (previousDir == 5)
                        cout << "Turn Right" << endl;
                    else if (previousDir == 6)
                        cout << "Turn Right" << endl;
                    else if (previousDir == 7)    
                        cout << "Follow road around" << endl;
                }else if(currentDir == 4){
                    if(previousDir == 0)
                        cout << "Follow road around" << endl;
                    else if (previousDir == 1)
                        cout << "Turn Left" << endl; 
                    else if (previousDir == 2)
                        cout << "Turn Left" << endl; 
                    else if (previousDir == 3)
                        cout << "Turn Left" << endl; 
                    else if (previousDir == 4)
                        cout << "Continue to go straight" << endl;
                    else if (previousDir == 5)
                        cout << "Turn Right" << endl;
                    else if (previousDir == 6)
                        cout << "Turn Right" << endl;
                    else if (previousDir == 7)    
                        cout << "Turn Right" << endl;
                }else if(currentDir == 5){
                    if(previousDir == 0)
                        cout << "Turn Right" << endl;
                    else if (previousDir == 1)
                        cout << "Follow road around" << endl;
                    else if (previousDir == 2)
                        cout << "Turn Left" << endl; 
                    else if (previousDir == 3)
                        cout << "Turn Left" << endl; 
                    else if (previousDir == 4)
                        cout << "Turn Left" << endl; 
                    else if (previousDir == 5)
                        cout << "Continue to go straight" << endl;
                    else if (previousDir == 6)
                        cout << "Turn Right" << endl;
                    else if (previousDir == 7)    
                        cout << "Turn Right" << endl;
                }else if(currentDir == 6){
                    if(previousDir == 0)
                        cout << "Turn Right" << endl;
                    else if (previousDir == 1)
                        cout << "Turn Right" << endl;
                    else if (previousDir == 2)
                        cout << "Follow road around" << endl;
                    else if (previousDir == 3)
                        cout << "Turn Left" << endl; 
                    else if (previousDir == 4)
                        cout << "Turn Left" << endl; 
                    else if (previousDir == 5)
                        cout << "Turn Left" << endl; 
                    else if (previousDir == 6)
                        cout << "Continue to go straight" << endl;
                    else if (previousDir == 7)    
                        cout << "Turn Right" << endl;
                }else if(currentDir == 7){
                    if(previousDir == 0)
                        cout << "Turn Right" << endl;
                    else if (previousDir == 1)
                        cout << "Turn Right" << endl;
                    else if (previousDir == 2)
                        cout << "Turn Right" << endl;
                    else if (previousDir == 3)
                        cout << "Follow road around" << endl;
                    else if (previousDir == 4)
                        cout << "Turn Left" << endl; 
                    else if (previousDir == 5)
                        cout << "Turn Left" << endl; 
                    else if (previousDir == 6)
                        cout << "Turn Left" << endl; 
                    else if (previousDir == 7)    
                        cout << "Continue to go straight" << endl;
                } 
            }else{
                firstTurn = false;
            }
            
            if (northOrSouth != " Straight " && eastOrWest != "Straight")
                cout << directionCount << ") Travel"  << northOrSouth << eastOrWest << " along " << streetName << endl;
            else if (northOrSouth != " Straight " && eastOrWest == "Straight")
                cout << directionCount << ") Travel" << northOrSouth << " along " << streetName << endl;
            else if (northOrSouth == " Straight " && eastOrWest != "Straight")
                cout << directionCount << ") Travel" << eastOrWest << " along " << streetName << endl;
            else 
                cout << directionCount << ") Continue to go straight along " << streetName << endl;
            
            previousString = streetName;
            directionCount++;
            
            previousDir = currentDir;
        }

        i = i + counter - 2;
        
    }
    
    cout << directionCount << ") Arrive at destination: " << destination << endl;
    cout << "Total travel time: " << int(compute_path_travel_time(path)) << " minutes" << endl;
}


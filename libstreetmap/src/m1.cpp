#include <vector>

#include "m1.h"

#define ERROR_VALUE 999999999
#define INF 99999999999

using namespace std;

// Pointer to singleton class of data structures
MapDatabase* mapDatabase = MapDatabase::getSingletonPointer();
map<unsigned, double> distances;
map<unsigned, double> unvisitedIntersections;

// Global variables to indicate which POIs are to be drawn
// Initialized as true so all are initially drawn
extern bool allPOIsClicked,
        coffeeClicked, 
        bankClicked, 
        foodClicked,
        churchClicked,
        pharmaClicked,
        healthClicked,
        otherPOIsClicked,
        oneWaysClicked,
        searchClicked;

extern vector<unsigned> path;

void setDijkstraDatabase();

// Load the map
bool load_map(std::string map_name) {
    bool load_success = loadStreetDatabaseBIN(map_name);
    
    // If map does not exist, output error message and terminate program right away
    if (!load_success) {
        return load_success;
    }
    
    mapDatabase -> MapDatabase::getSingletonPointer();
    
    // Set size of vector<vector<>> data structures in singleton
    mapDatabase->resize_intersectionAndStreetSeg();
    mapDatabase->resize_StreetStreetSegments();
    mapDatabase->resize_StreetSegmentLengths();
    mapDatabase->resize_StreetSegmentTravelTimes();
    mapDatabase->resize_IntersectionGraph();
    
    // Create intersections data structure
    for (unsigned i = 0; i < getNumberOfIntersections(); i++) {
        mapDatabase->addInterections(getIntersectionName(i), i);
    }
    
    // Create streets data structure
    for (unsigned i = 0; i < getNumberOfStreets(); i++) {
        mapDatabase->addStreet(getStreetName(i), i);
    }
    
    // Create intersection and street segment graph
    for (unsigned intersectionID = 0; intersectionID < getNumberOfIntersections(); intersectionID++) {
        for (unsigned j = 0; j < getIntersectionStreetSegmentCount(intersectionID); j++) {
            mapDatabase->addStreetSegmentToIntersection(intersectionID, j);
        }
    }
    
    // Create points of interest data structure
    for (unsigned i = 0; i < getNumberOfPointsOfInterest(); i++) {
        mapDatabase->addPointOfInterest(i);
    }
    
    // Create vector of associated street segments for each street
    for (unsigned streetSegID = 0; streetSegID < getNumberOfStreetSegments(); streetSegID++) {
        mapDatabase->addStreetStreetSegments(streetSegID);
    }
    
     // Get intersection IDs of both extremities of street segment
    for (unsigned streetSeg = 0; streetSeg < getNumberOfStreetSegments(); streetSeg++) {
        mapDatabase->addStreetSegmentLengths(streetSeg);
    }
    
    // Add travel time data to streetSegmentTravelTimes data structure
    for (unsigned streetSeg = 0; streetSeg < getNumberOfStreetSegments(); streetSeg++) {
        mapDatabase->addStreetSegmentTravelTimes(streetSeg);
    }
        
    for (unsigned streetSeg = 0; streetSeg < getNumberOfStreetSegments(); streetSeg++) {
        mapDatabase->addStreetLengths(streetSeg);
    }
    
    mapDatabase->addNodeAndEdge();
       
    //setDijkstraDatabase();
    
    // Call function from m2.cpp that adds the necessary data to the featureIDtoValue and featureIDtoPoints maps declared in DataStructures
    addFeaturesToDatabase();
    
    return load_success;
}

// Close the map
void close_map() {
    // Deletes the running instance of mapDatabase
    mapDatabase->DeleteInstance();
    
    // Reset buttons
    allPOIsClicked = true,
    coffeeClicked = true, 
    bankClicked = true, 
    foodClicked = true,
    churchClicked = true,
    pharmaClicked = true,
    healthClicked = true,
    otherPOIsClicked = true,
    oneWaysClicked = true,
    searchClicked = false;
    
    path.clear();
    
    closeStreetDatabase();
}

void setDijkstraDatabase() {
    for (unsigned intersection = 0; intersection < getNumberOfIntersections(); intersection++) {
        distances[intersection] = INF;
        unvisitedIntersections.insert(make_pair(intersection, INF));
    }
}
// Return intersection id for an intersection name
unsigned find_intersection_id_from_name(string intersectionName) {
    return mapDatabase-> getIntersectionId(intersectionName);
}

// Returns street id for an street name
unsigned find_street_id_from_name(string streetName) {
    return mapDatabase->getStreetId(streetName);
}

// Return the street segments for a given intersection name
vector<unsigned> find_intersection_street_segments(string intersectionName) {
    vector<unsigned> intersectionStreetSegmentsIDs;
    unsigned intersectionID = mapDatabase->getIntersectionId(intersectionName);

    // Gets the street segments IDs vector associated with intersection_name from 
    // intersection_and_streetSeg_graph
    intersectionStreetSegmentsIDs = mapDatabase->getIntersectionAdjStreetSegments(intersectionID);
    
    return intersectionStreetSegmentsIDs;
}

// Return the street segments for a given intersectionID
vector<unsigned> find_intersection_street_segments(unsigned intersectionID) {
    vector<unsigned> intersectionStreetSegmentsIDs;

    // Gets the street segments IDs vector associated with intersection_id from 
    // intersection_and_streetSeg_graph 
    intersectionStreetSegmentsIDs = mapDatabase->getIntersectionAdjStreetSegments(intersectionID);
    
    return intersectionStreetSegmentsIDs;
}

// Returns street names at an intersection
vector<string> find_intersection_street_names(string intersection_name) {
    vector<string> intersectionStreetNames;
    vector<unsigned> intersectionStreetSegmentsIDs;
    
    unsigned intersectionID = find_intersection_id_from_name(intersection_name);
    
    intersectionStreetSegmentsIDs = mapDatabase->getIntersectionAdjStreetSegments(intersectionID);
    
    // Used for unit test error checking
    if (intersectionStreetSegmentsIDs[0] == ERROR_VALUE) // same as: if (intersectionStreetSegmentsIDs == {999999999}); 
    {
        return {"Fake Street Name"};
    }
    // error checking end
    
    for (unsigned i = 0; i < intersectionStreetSegmentsIDs.size(); i++) {
        intersectionStreetNames.push_back(getStreetName(getStreetSegmentStreetID(intersectionStreetSegmentsIDs[i])));
    }
    
    // Remove duplicate street names
    sort(intersectionStreetNames.begin(), intersectionStreetNames.end());
    intersectionStreetNames.erase(unique(intersectionStreetNames.begin(), intersectionStreetNames.end()), intersectionStreetNames.end());
    
    return intersectionStreetNames;
}

// Returns street names at an intersection
vector<string> find_intersection_street_names(unsigned intersectionID) {
    vector<string> intersectionStreetNames;
    vector<unsigned> intersectionStreetSegmentsIDs;
       
    // Gets the street segments vector associated with intersection_name and appends to back
    // of intersectionStreetNames vector
    intersectionStreetSegmentsIDs = mapDatabase-> getIntersectionAdjStreetSegments(intersectionID);
    
    for (unsigned i = 0; i < intersectionStreetSegmentsIDs.size(); i++) {
        intersectionStreetNames.push_back(getStreetName(getStreetSegmentStreetID(intersectionStreetSegmentsIDs[i])));
    }

    // Remove duplicate street names
    sort(intersectionStreetNames.begin(), intersectionStreetNames.end());
    intersectionStreetNames.erase(unique(intersectionStreetNames.begin(), intersectionStreetNames.end()), intersectionStreetNames.end());
    
    return intersectionStreetNames;
}

// Determines if intersection_name1 and intersection_name2 are connected by a single street segment
bool are_directly_connected (string intersection_name1, string intersection_name2) {
    // Intersections are connected by default if they are the same 
    if (intersection_name1 == intersection_name2) {
        return true;
    }
    
    vector<unsigned> intsAdjToInt1 = find_adjacent_intersections(intersection_name1);
    unsigned intersectionID2 = find_intersection_id_from_name(intersection_name2);

    // Compare adjacent intersection IDs to first intersection with intersectionID of second  
    for(unsigned i = 0; i < intsAdjToInt1.size(); i++){
        if (intsAdjToInt1[i] == intersectionID2) {
            return true;
        }
    }
    
    return false; // Return false if a match was not made
}

// Find all intersections connected by one street segment from given intersection
vector<unsigned> find_adjacent_intersections(string intersection_name){
    unsigned intersectionID = find_intersection_id_from_name(intersection_name);
    vector<unsigned> adjacentIntersections;
    vector<unsigned> adjacentStreetSegments = mapDatabase->getIntersectionAdjStreetSegments(intersectionID);
    StreetSegmentEnds segmentEnds;
    unsigned fromInt, toInt;
    
    for (unsigned segNum = 0; segNum < adjacentStreetSegments.size(); segNum++) {
        segmentEnds = getStreetSegmentEnds(adjacentStreetSegments[segNum]);
        fromInt = segmentEnds.from;
        toInt = segmentEnds.to;
        
        if (fromInt == intersectionID) {
            adjacentIntersections.push_back(toInt);      
        } else if (!getStreetSegmentOneWay(adjacentStreetSegments[segNum])) {
            adjacentIntersections.push_back(fromInt);
        }
    }
    
    sort(adjacentIntersections.begin(), adjacentIntersections.end());
    adjacentIntersections.erase(unique(adjacentIntersections.begin(), adjacentIntersections.end()), adjacentIntersections.end());
    
    return adjacentIntersections;
}

// For a given street, return all the street segments
vector<unsigned> find_street_street_segments(string street_name) {
    unsigned streetID = find_street_id_from_name(street_name);
    return mapDatabase->getStreetStreetSegments(streetID);
}

// For a given street, find all the intersections
vector<unsigned> find_all_street_intersections(string street_name) {
    vector<unsigned> streetSegments; 
    vector<unsigned> streetIntersections;
    
    // Make a vector of the street_name street segments  
    streetSegments = find_street_street_segments(street_name);
    StreetSegmentEnds segmentEnds; 
    
    // Get the end points(intersections)for each street segment
    for(unsigned i = 0; i < streetSegments.size(); i++) {
        segmentEnds = getStreetSegmentEnds(streetSegments[i]);
        streetIntersections.push_back(segmentEnds.from);
        streetIntersections.push_back(segmentEnds.to);
    }
    
    // Sort the intersections and delete the duplicates
    sort(streetIntersections.begin(), streetIntersections.end());
    streetIntersections.erase(unique(streetIntersections.begin(), streetIntersections.end()), streetIntersections.end());
    
    return streetIntersections;
}

// Find distance between two coordinates (meters)
double find_distance_between_two_points(LatLon point1, LatLon point2) {
    // Convert to (x,y)
    double xcoord1 = DEG_TO_RAD*point1.lon * cos( (DEG_TO_RAD*point1.lat + DEG_TO_RAD*point2.lat) / 2 );
    double ycoord1 = DEG_TO_RAD*point1.lat;
    double xcoord2 = DEG_TO_RAD*point2.lon * cos( (DEG_TO_RAD*point1.lat + DEG_TO_RAD*point2.lat) / 2 );
    double ycoord2 = DEG_TO_RAD*point2.lat;
    
    // Pythagoras' theorem
    double distance = EARTH_RADIUS_IN_METERS * (sqrt( pow( (ycoord2 - ycoord1), 2.0 ) + pow( (xcoord2 - xcoord1), 2.0 ) ));

    return distance;
}

// Find the length of a given street segments (meters)
double find_street_segment_length(unsigned street_segment_id) {
    return mapDatabase->getStreetSegmentLengths(street_segment_id)[0];
}

// Find the length of a whole street (meters)
double find_street_length(std::string street_name) {
    // Use street segments to compute total street length
    vector<unsigned> allSegmentsOnStreet = find_street_street_segments(street_name);
    
    double streetLength = 0;
    
    for (auto iter = allSegmentsOnStreet.begin(); iter != allSegmentsOnStreet.end(); iter++){
        streetLength += find_street_segment_length(*iter);
    }
    
    return streetLength;
}

// Find the travel time to drive a street segment (time(minutes) = distance(Km)/speed_limit(Km/h)*60)
double find_segment_travel_time(unsigned street_segment_id) {        
    return mapDatabase->getStreetSegmentTravelTimes(street_segment_id)[0];
}

// Find the nearest point of interest (by name) to a given position
std::string find_closest_point_of_interest(LatLon my_position) {
    string closestPOIname = "Error: Could not find POI";
    double closestPOIdistance = -1; 
    double distanceBetweenPoints;
    LatLon poi;

    for (auto iter = mapDatabase->POI_beginIter(); iter != mapDatabase->POI_endIter(); iter++) {
        poi = iter->second;
        distanceBetweenPoints = find_distance_between_two_points(my_position, poi);

        if ((distanceBetweenPoints < closestPOIdistance) || (closestPOIdistance == -1)){
            closestPOIdistance = distanceBetweenPoints;
            closestPOIname = getPointOfInterestName(iter->first);
        }
    }
    
    return closestPOIname;
}

#include <queue>
#include <algorithm>

#include "AStarFunctions.h"
#include "StreetEdge.h"
#include "MapDatabase.h"
#include "m2.h"

#define ERROR_VALUE 999999999
#define INITIALIZE_VALUE 0
#define INF 99999999999

extern MapDatabase* mapDatabase;
extern map<unsigned, double> distances;
extern map<unsigned, double> unvisitedIntersections;

// Prototypes
vector<unsigned> reconstructPath(map<unsigned, unsigned> came_from, unsigned current);

vector<unsigned> AStarAlgorithm(unsigned startId, unsigned goalId) {
    vector<unsigned> failure = {ERROR_VALUE};
    
    if (startId != ERROR_VALUE && goalId != ERROR_VALUE) {
        map<unsigned, double> distance;
        map<unsigned, unsigned> previous;
        map<unsigned, double> unvisitedIntersections;
        
        unsigned currentIntersection;
        unsigned intersectionId, neighbourIntersection;
        
        double streetSegSpeedLimit;
        
        double alt;
       
        bool in_came_from = false;
        
        unvisitedIntersections[startId] = 0;
        distances[startId] = 0; 
        previous[startId] = ERROR_VALUE;
        
        while (!unvisitedIntersections.empty()) {
            currentIntersection = lowestFScoreNode(unvisitedIntersections);
            
            if (currentIntersection == goalId) {
                return reconstructPath(previous, goalId); 
            }
            
            unvisitedIntersections.erase(unvisitedIntersections.find(currentIntersection));
            
            for (unsigned neighbour = 0; neighbour < mapDatabase->getStreetEdges(currentIntersection).size(); neighbour++) {
                neighbourIntersection = mapDatabase->getStreetEdges(currentIntersection)[neighbour].getTargetIntersection();
                
                streetSegSpeedLimit = getStreetSegmentSpeedLimit(getSegmentBetweenIntersections(currentIntersection, neighbourIntersection));
                
                alt = distances[currentIntersection]/streetSegSpeedLimit + mapDatabase->getStreetEdges(currentIntersection)[neighbour].getEdgeWeight();
                
                if (alt < distances[neighbourIntersection]){
                    distances[neighbourIntersection] = alt;
                    unvisitedIntersections[neighbourIntersection] = alt;
                    // Change neighbor's came_from intersection to current intersection
                    for (auto iter = previous.begin(); iter != previous.end(); iter++) {  
                        if ((*iter).first == neighbourIntersection) {
                            (*iter).second = currentIntersection;
                            in_came_from = true;
                        }
                    } 

                    // If neighbor intersection is not in the came_from map, add it
                    if (!in_came_from) {
                        previous.insert(make_pair(neighbourIntersection, currentIntersection));
                    }

                }
                
                in_came_from = false;
            }
        }
    }
}

// this does not account for "(unknown)" street names
double addTurnTimeMin (unsigned ssIDfrom, unsigned ssIDto) {
    if (ssIDfrom != ERROR_VALUE && ssIDto != ERROR_VALUE) {
        double turnTimeMin = INITIALIZE_VALUE;

        // Get street ID to which the street segment belongs
        unsigned streetIDfrom = getStreetSegmentStreetID(ssIDfrom);
        unsigned streetIDto = getStreetSegmentStreetID(ssIDto);

        // Get street name from ID
        string streetNamefrom = getStreetName(streetIDfrom);
        string streetNameto = getStreetName(streetIDto);

        // If change streets --> turn required
        if (streetNamefrom.compare(streetNameto) != 0) {
            turnTimeMin = 0.25; // Convert TIMETOTURN to minutes
        } else {  // If still on same street -> no turn required
            turnTimeMin = 0;
        }

        return turnTimeMin;
    } else {
        return 0;
    }
}

// Returns intersection from the open set which has the lowest f score
unsigned lowestFScoreNode (map<unsigned, double> openSet) {
    double f_score_lowest = INF;
    unsigned bestNode = 0;
 
    for (auto iter = openSet.begin(); iter != openSet.end(); iter++) {       
        if ((*iter).second < f_score_lowest) {
            f_score_lowest = (*iter).second;
            bestNode = (*iter).first;
        }
    }
    
    return bestNode;
}

// Rebuilds came_from map to create traversable path
vector<unsigned> reconstructPath(map<unsigned, unsigned> came_from, unsigned current) {
    vector<unsigned> total_path; // Reconstructed path
    vector<unsigned> path_segments; // Vector of segments between the intersections in came_from
    
    // Add the goal id to path
    total_path.push_back(current);
    
       // We have reached the beginning intersection if current = ERROR_VALUE
    // or we have reached the end of the came_from map
    while (came_from.find(current) != came_from.end() || current != ERROR_VALUE) {
        // Get the intersection id that the current intersection came from
        current = came_from[current];
        
        total_path.push_back(current);
    }
    
    // Take off ERROR_VALUE from the total_path
    total_path.pop_back();
    

    // Make a vector of street segments from vector of intersections
    for (unsigned i = 0; i < total_path.size()-1; i++) {        
        path_segments.push_back(getSegmentBetweenIntersections (total_path[i], total_path[i+1]));
    }
    
    // Reverse the order of the path so that the first element is the start intersection
    reverse(path_segments.begin(), path_segments.end());
    
    return path_segments;
}

unsigned getSegmentBetweenIntersections (unsigned intersectionID1, unsigned intersectionID2) {
    unsigned intersection_street_seg1, intersection_street_seg2;
    unsigned commonSegmentId = INITIALIZE_VALUE;
    unsigned fastestCommonSegment = INITIALIZE_VALUE;
    double segmentTravelTime = INITIALIZE_VALUE;
    double fastestTravelTime = 9999999;
    vector<unsigned> segments;

    bool oneWaySafe = false;
    
    StreetSegmentEnds segmentEnds;  // Intersections at either end of a street segment
    unsigned long toInt;
    
    // Segments adjacent to intersection 1
    for (unsigned segment1 = 0; segment1 < getIntersectionStreetSegmentCount(intersectionID1); segment1++) {
        intersection_street_seg1 = getIntersectionStreetSegment(intersectionID1, segment1);

        // Segments adjacent to intersection 2
        for (unsigned segment2 = 0; segment2 < getIntersectionStreetSegmentCount(intersectionID2); segment2++) {
            intersection_street_seg2 = getIntersectionStreetSegment(intersectionID2, segment2);

            // If the two street segments are adjacent
            if (intersection_street_seg1 == intersection_street_seg2) {
                commonSegmentId = intersection_street_seg1;
                segmentEnds = getStreetSegmentEnds(commonSegmentId);
                toInt = segmentEnds.to;
                
                if (getStreetSegmentOneWay(commonSegmentId)){
                    if (intersectionID1 == toInt)
                        oneWaySafe = true;
                    else{
                        oneWaySafe = false;
                    }
                }else{
                        oneWaySafe = true;
                }
                segmentTravelTime = find_segment_travel_time(commonSegmentId);

                // Check to see if the segment travel time is faster than others segments pointing from 
                // intersection 1 to intersection 2
                if (segmentTravelTime < fastestTravelTime && oneWaySafe) {
                    fastestCommonSegment = commonSegmentId;
                    fastestTravelTime = segmentTravelTime;

                }              
            }
        }
    }
                       
    // Return the specified street segment
    return fastestCommonSegment;
}
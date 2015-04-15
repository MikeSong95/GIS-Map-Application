#include <vector>
#include <algorithm>

#include "MapDatabase.h"

// Initialize objectPointer to NULL
MapDatabase* MapDatabase::singletonPointer = NULL; // or NULL, or nullptr in c++11

// Return DataStructures* objectPointer
MapDatabase* MapDatabase::getSingletonPointer() {
    if (singletonPointer == NULL) {
         singletonPointer = new MapDatabase;
    }
    
    return (singletonPointer);
}

// Deletes the running instance of mapDatabase
void MapDatabase::DeleteInstance() {
    delete singletonPointer; // Works even if the pointer is NULL (does nothing then)
    singletonPointer = NULL;
}

// -------------------------------------- CONSTRUCTOR -------------------------------------- //
MapDatabase::MapDatabase() {
    // Do not implement
}

// -------------------------------------- DESTRUCTOR -------------------------------------- //
MapDatabase::~MapDatabase() {
    // Do not implement
}

// -------------------------------------- SAFETY OVERRIDES -------------------------------------- //
    MapDatabase::MapDatabase(const MapDatabase& orig) {
    // Do not implement
}
    void MapDatabase::operator=(MapDatabase const&) {
    // Do not implement
}
    
    
// -------------------------------------- "ADD" MUTATORS -------------------------------------- // 
void MapDatabase::addInterections(string intersectionName, unsigned id) {
    singletonPointer->intersections.insert(make_pair(intersectionName, id));
}

void MapDatabase::addStreet(string streetName, unsigned id) {
    singletonPointer->streets.insert(make_pair(streetName, id));
}

void MapDatabase::addStreetSegmentToIntersection(unsigned intersectionId, unsigned intersectonStreetSegId) {
    singletonPointer->intersection_and_streetSeg_adjList[intersectionId].push_back(getIntersectionStreetSegment(intersectionId,intersectonStreetSegId));
}

void MapDatabase::addPointOfInterest(unsigned id) {
    singletonPointer->POI.insert(make_pair(id, getPointOfInterestPosition(id)));
}

void MapDatabase::addStreetStreetSegments(unsigned streetSegmentId) {
    singletonPointer->streetStreetSegments[getStreetSegmentStreetID(streetSegmentId)].push_back(streetSegmentId);
}

void MapDatabase::addStreetSegmentLengths(unsigned streetSegmentId) {
    StreetSegmentEnds segmentEnds = getStreetSegmentEnds(streetSegmentId);

    // Get lat/lon of both extremities of street segment
    LatLon ssEnd1Position = getIntersectionPosition(segmentEnds.from);
    LatLon ssEnd2Position = getIntersectionPosition(segmentEnds.to);

    double ssLength = 0;

    // Start at beginning extremity
    LatLon PREVssCurvePointPosition = ssEnd1Position;

    // Get # of curve points on street segment
    unsigned int ssCurvePointCount = getStreetSegmentCurvePointCount(streetSegmentId);

    // Add up all straight lines on curved street segments
    for (unsigned int i = 0; i < ssCurvePointCount; i++) {
        LatLon ssCurvePointPosition = getStreetSegmentCurvePoint(streetSegmentId, i);

        ssLength += find_distance_between_two_points(PREVssCurvePointPosition, ssCurvePointPosition);

        PREVssCurvePointPosition = ssCurvePointPosition;
    }

    // Add final straight line to total ssLength
    ssLength += find_distance_between_two_points(PREVssCurvePointPosition, ssEnd2Position);

    streetSegmentLengths[streetSegmentId].push_back(ssLength); 
}

void MapDatabase::addStreetLengths(unsigned streetSeg) {
    
    double segLength = 0;
    segLength = find_street_segment_length(streetSeg);
    unsigned streetId = getStreetSegmentStreetID(streetSeg);

    singletonPointer-> streetLengths[streetId] += segLength;
}

void MapDatabase::addStreetSegmentTravelTimes(unsigned streetSegmentId) {
    double travelTimeMin = 60 * (getStreetSegmentLengths(streetSegmentId)[0] / 1000) / getStreetSegmentSpeedLimit(streetSegmentId);
            
    streetSegmentTravelTimes[streetSegmentId].push_back(travelTimeMin);
}

void MapDatabase::addFeatureValue(unsigned featureID, string featureValue) {
    singletonPointer->featureIDtoValue.insert(make_pair(featureID, featureValue));
}

void MapDatabase::addFeaturePoints(unsigned featureID, t_point* featurePoints) {
    singletonPointer->featureIDtoPoints.insert(make_pair(featureID, featurePoints));
}

void MapDatabase::addNodeAndEdge() {   
    double segmentTraversalTime;    // The time to traverse that street segment
    StreetSegmentEnds segmentEnds;  // Intersections at either end of a street segment
    unsigned long fromInt, toInt;   // Intersection Ids at either end of a street segment
    vector <StreetEdge> edges;
    StreetEdge edge;
    
    // Create intersection and streets graph - directed adjacency list 
    // Nodes are intersections, edges are streets
    // Edge weights are determined by the time it takes to traverse that street
    for (unsigned intersectionID = 0; intersectionID < getNumberOfIntersections(); intersectionID++) {
        vector<unsigned> adjacentSegments = find_intersection_street_segments(intersectionID);
        
        for (auto iter = adjacentSegments.begin(); iter != adjacentSegments.end(); iter++) {
            segmentEnds = getStreetSegmentEnds(*iter);
            fromInt = segmentEnds.from;
            toInt = segmentEnds.to;
            
            // Determines which intersection the street points to
            if (getStreetSegmentOneWay(*iter)) {
                if (intersectionID == fromInt) {
                    segmentTraversalTime = find_segment_travel_time(*iter);
                    edge = StreetEdge(toInt, segmentTraversalTime); 
                    edges.push_back(edge);
                }
            } else {
                if (fromInt == intersectionID) {
                    segmentTraversalTime = find_segment_travel_time(*iter);
                    edge = StreetEdge(toInt, segmentTraversalTime); 
                    edges.push_back(edge);
                } else {
                    segmentTraversalTime = find_segment_travel_time(*iter);
                    edge = StreetEdge(fromInt, segmentTraversalTime); 
                    edges.push_back(edge);
                }
            }
        }
        
        intersectionGraph[intersectionID] = edges;
        edges.clear();
    }
}

// -------------------------------------- "RESIZE" MUTATORS -------------------------------------- // 
// Set size to all intersections
void MapDatabase::resize_intersectionAndStreetSeg() {
    intersection_and_streetSeg_adjList.resize(getNumberOfIntersections());
}

// Set size to all streets
void MapDatabase::resize_StreetStreetSegments(){
    streetStreetSegments.resize(getNumberOfStreets());
}

// Set size to all street segments
void MapDatabase::resize_StreetSegmentLengths() {
    streetSegmentLengths.resize(getNumberOfStreetSegments());
}

// Set size to all street segment travel times vectors
void MapDatabase::resize_StreetSegmentTravelTimes() {
    streetSegmentTravelTimes.resize(getNumberOfStreetSegments());
}

void MapDatabase::resize_IntersectionGraph() {
    singletonPointer->intersectionGraph.resize(getNumberOfIntersections());
}

void MapDatabase::reset_streetEdgeScores() {
    vector<StreetEdge> streetEdges;
    
    for (unsigned i = 0; i < getNumberOfIntersections(); i++) {
        streetEdges = intersectionGraph[i];
        
        for (unsigned j = 0; j < streetEdges.size(); j++) {
            singletonPointer->intersectionGraph[i][j].set_g_score(0);
            singletonPointer->intersectionGraph[i][j].set_h_score(0);
            singletonPointer->intersectionGraph[i][j].set_f_score();
        }
    }
}

// -------------------------------------- ACCESSORS -------------------------------------- //
// Returns the id of the intersection name
unsigned MapDatabase::getIntersectionId(string intersectionName) {
    if(intersections.find(intersectionName) == intersections.end()) {
        //cout << "ERROR: Could not find: " << intersectionName << "!" << endl;
        return 999999999;
    }
            
    return intersections[intersectionName];
}

// Returns the id of the street name
unsigned MapDatabase::getStreetId(string streetName) {
    if(streets.find(streetName) == streets.end()) {
        cout << "ERROR: Could not find: " << streetName << "!" << endl;
        return 999999999;
    }
            
    return streets[streetName];
}

// Returns a vector containing the adjacent street segments attached to intersection, # intersectionId
vector<unsigned> MapDatabase::getIntersectionAdjStreetSegments(unsigned intersectionId) {
    if (intersectionId >= getNumberOfIntersections()) {
        cout << "ERROR: Could not find intersectionId: " << intersectionId << "!" << endl;
        return {999999999};
    }
            
    return intersection_and_streetSeg_adjList[intersectionId];
}
    
// Return the Lat/Lon position of point of interest #, pointOfInterestId
LatLon MapDatabase::getPointOfInterest(unsigned pointOfInterestId) {
    return POI[pointOfInterestId];
}

// Return POI data structure
map<unsigned, LatLon> MapDatabase::getPointOfIntersectionMap() {
    return POI;
}

map<unsigned, double> MapDatabase::getStreetLengthsMap(){
    return streetLengths;
}

double MapDatabase::getStreetLengths(unsigned streetId) {
    return streetLengths[streetId];
}
// Returns a vector containing all street segments of street streetId
vector<unsigned> MapDatabase::getStreetStreetSegments(unsigned streetId) {    
    return streetStreetSegments[streetId];
} 
        
// Returns a vector containing all the computed lengths of street segment
vector<double> MapDatabase::getStreetSegmentLengths(unsigned streetSegmentId) {
    return streetSegmentLengths[streetSegmentId];
}
      
// Returns a vector containing all the computed travel times of street segment
vector<double> MapDatabase::getStreetSegmentTravelTimes(unsigned streetSegmentId) {
    return streetSegmentTravelTimes[streetSegmentId];
}

// Returns the feature value (i.e. attribute) of a specific featureID
string MapDatabase::getFeatureValue(unsigned featureID) {
    return featureIDtoValue[featureID];
}

// Returns the list of LatLon points that define a specific featureID
t_point* MapDatabase::getFeaturePoints(unsigned featureID) {
    return featureIDtoPoints[featureID];
}

vector<StreetEdge>& MapDatabase::getStreetEdges(unsigned intersectionId) {
    return intersectionGraph[intersectionId];
}
#pragma once

#include <map>

#include "graphics.h"
#include "m1.h"
#include "StreetEdge.h"

using namespace std;

class MapDatabase {
    private:
        // Pointer to this singleton class
        static MapDatabase* singletonPointer;
        
// -------------------------------------- CONSTRUCTOR -------------------------------------- //
        MapDatabase();
        
// -------------------------------------- SAFETY OVERRIDES -------------------------------------- //
        MapDatabase(const MapDatabase& orig);
        void operator=(MapDatabase const&);
        
// -------------------------------------- DATABASES -------------------------------------- //
        // Intersection database: <intersection name, intersection id> 
        map<string,unsigned> intersections; 
        // Streets database: <street name, street id>
        map<string,unsigned> streets;
        // Intersections and street segment graph. Initialize to 1 for compilation.
        // Intersection -> street segments vector
        vector< vector<unsigned> > intersection_and_streetSeg_adjList;
        // Points of interest database: <POIid, (Lat,Lon)>
        map<unsigned, LatLon> POI;
        // All street segments for each street
        vector< vector<unsigned> > streetStreetSegments; 
        // All street segment lengths
        vector< vector<double> > streetSegmentLengths;
        // All street lengths
        map <unsigned, double> streetLengths;  
        // All street segment travel times
        vector< vector<double> > streetSegmentTravelTimes;
        // Features database to find return value: <feature ID, feature return value>
        map<unsigned,string> featureIDtoValue;
        // Features database to find comprising LatLon points: <feature ID, XY points>
        map<unsigned,t_point*> featureIDtoPoints;
        // Intersections graph (weighted directed adjacency list)
        // Nodes are intersections, edges are street segments
        // Weights are determined by the time it takes to traverse that street segment
        vector < vector<StreetEdge> > intersectionGraph;

    public:
        // Return DataStructures* objectPointer
        static MapDatabase* getSingletonPointer();

        // Delete object pointer
        static void DeleteInstance();
        
// -------------------------------------- DESTRUCTOR -------------------------------------- //
        ~MapDatabase();
        
// -------------------------------------- "ADD" MUTATORS -------------------------------------- //
        void addInterections(string intersectionName, unsigned id);
        void addStreet(string streetName, unsigned id);
        void addStreetSegmentToIntersection(unsigned intersectionId, unsigned intersectonStreetSegId);
        void addPointOfInterest(unsigned id);
        void addStreetStreetSegments(unsigned streetSegmentId);
        void addStreetSegmentLengths(unsigned streetSegmentId);
        void addStreetLengths(unsigned streetSeg);
        void addStreetSegmentTravelTimes(unsigned streetSegmentId);
        void addFeatureValue(unsigned featureID, string featureValue);
        void addFeaturePoints(unsigned featureID, t_point* featurePoints);
        void addNodeAndEdge();
        
// -------------------------------------- "RESIZE" MUTATORS -------------------------------------- // 
        // Set size to all intersections
        void resize_intersectionAndStreetSeg();
        // Set size to all streets
        void resize_StreetStreetSegments();
        // Set size to all street segments
        void resize_StreetSegmentLengths();
        // Set size to all street segment travel times vectors
        void resize_StreetSegmentTravelTimes();
        // Sets size of intersection graph
        void resize_IntersectionGraph();
        
        void reset_streetEdgeScores();
        
// -------------------------------------- ACCESSORS -------------------------------------- //
        // Prevent use of singular iterator
        map<unsigned,LatLon>::const_iterator POI_beginIter() const { return POI.begin(); }
        map<unsigned,LatLon>::const_iterator POI_endIter() const { return POI.end(); }
             
        // Returns the id of the intersection name
        unsigned getIntersectionId(string intersectionName);
        // Returns the name of the intersection id
        // Returns the id of the street name
        unsigned getStreetId(string streetName);
        // Returns a vector containing the adjacent street segments attached to intersection #, intersectionId
        vector<unsigned> getIntersectionAdjStreetSegments(unsigned intersectionId);
        // Return the Lat/Lon position of point of interest #, pointOfInterestId
        LatLon getPointOfInterest(unsigned pointOfInterestId);
        map<unsigned, LatLon> getPointOfIntersectionMap();
        // Returns street length
        double getStreetLengths(unsigned streetId);
        map<unsigned, double> getStreetLengthsMap();
        // Returns a vector containing all street segments of street streetId
        vector<unsigned> getStreetStreetSegments(unsigned streetId);
        // Returns a vector containing all the computed lengths of street segment
        vector<double> getStreetSegmentLengths(unsigned streetSegmentId);
        // Returns a vector containing all the computed travel times of street segment
        vector<double> getStreetSegmentTravelTimes(unsigned streetSegmentId);
        // Returns the feature value (i.e. attribute) of a specific featureID
        string getFeatureValue(unsigned featureID);
        // Returns the list of LatLon points that define a specific featureID
        t_point* getFeaturePoints(unsigned featureID); 
        // Returns the vector of street edges for an intersection from intersection graph
        vector <StreetEdge>& getStreetEdges(unsigned intersectionId);
};
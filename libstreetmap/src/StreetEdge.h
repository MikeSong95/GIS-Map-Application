#ifndef STREETEDGE_H
#define	STREETEDGE_H

#include "assert.h"
#include "StreetSegmentEnds.h"

// Edges in directed graph (adjacency list) in intersections graph
// Nodes are intersections, edges are streets
class StreetEdge {
    private:
        unsigned targetIntersection;    // Intersection street segments goes towards
        double weight_traversalTime;    // Defined as the length of time to traverse the edge
        double g_score;
        double h_score;
        double f_score;
    public:
// ------------------------------------- CONSTRUCTORS ------------------------------------- //
        StreetEdge();
        StreetEdge(unsigned targetIntersection_, double weight_);
        
// --------------------------------------- OVERRIDES -------------------------------------- //
        StreetEdge(const StreetEdge& orig);
        StreetEdge operator=(const StreetEdge& orig);
        
// -------------------------------------- DESTRUCTOR -------------------------------------- //
        virtual ~StreetEdge();
        
// -------------------------------------- MUTATORS -------------------------------------- //
        double set_g_score(double score);
        double set_h_score(double score);
        double set_f_score();
        
        void setPoiID(unsigned intersectionID);
        void setTravel(double distance);
        
// -------------------------------------- ACCESSORS -------------------------------------- //
        unsigned getTargetIntersection();
        double getEdgeWeight();
        double get_g_score();
        double get_h_score();
        double get_f_score();
};

#endif	/* STREETEDGE_H */
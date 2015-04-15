#include "StreetEdge.h"

StreetEdge::StreetEdge() {
}

StreetEdge::StreetEdge(unsigned targetIntersection_, double weight_) {
    targetIntersection = targetIntersection_;
    weight_traversalTime = weight_;
    
    g_score = 0;
    h_score = 0;
    f_score = 0; 
}

StreetEdge::StreetEdge(const StreetEdge& orig) {
    targetIntersection = orig.targetIntersection;
    weight_traversalTime = orig.weight_traversalTime;
    g_score = orig.g_score;
    f_score = orig.f_score;
}

StreetEdge StreetEdge::operator=(const StreetEdge& orig) {
    targetIntersection = orig.targetIntersection;
    weight_traversalTime = orig.weight_traversalTime;
    g_score = orig.g_score;
    f_score = orig.f_score;
    
    return *this;
 }
 
StreetEdge::~StreetEdge() {
    // Nothing to destroy
}

double StreetEdge::set_g_score(double score) {
    g_score = score;
}

double StreetEdge::set_h_score(double score) {
    h_score = score;
}

double StreetEdge::set_f_score() {
    f_score = g_score + h_score;
}
        
// Returns the intersection the street segment goes towards
unsigned StreetEdge::getTargetIntersection() {
    return targetIntersection;
}

// Returns the weight of this edge (street)
// Weight is defined by the time it takes to traverse this street segment
double StreetEdge::getEdgeWeight() {
    return weight_traversalTime;
}

double StreetEdge::get_g_score() {
    return g_score;
}

double StreetEdge::get_h_score() {
    return h_score;
}

double StreetEdge::get_f_score() {
    return f_score;
}


void StreetEdge::setPoiID(unsigned intersectionID){

    targetIntersection = intersectionID;
}


void StreetEdge::setTravel(double distance){
    
    weight_traversalTime = distance;
    
}
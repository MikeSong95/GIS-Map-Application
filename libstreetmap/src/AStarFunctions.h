#pragma once

#include "StreetsDatabaseAPI.h"
#include "m1.h"

#include <vector>
#include <string>

#define TIMETOTURNSEC 15

using namespace std;

extern MapDatabase* mapDatabase;

vector<unsigned> AStarAlgorithm(unsigned start, unsigned goal);

// Computes the straight-line travel time between 2 points at the highest city speed limit
double heuristic (unsigned currentIntersection, unsigned goalIntersection);

// this does not account for "(unknown)" street names
double addTurnTimeMin (unsigned ssIDfrom, unsigned ssIDto);

double addTurnTimeMin2 (unsigned ssIDfrom, unsigned ssIDto);

// Returns the maximum speed limit of the loaded city; helper function for A* heuristic
double getMaxSpeedLimit();

unsigned lowestFScoreNode (map<unsigned, double> openSet);

double computeFScore(unsigned node, unsigned goalNode, vector<unsigned> path);

// Returns the fastest street segment connecting two intersections
unsigned getSegmentBetweenIntersections (unsigned intersectionID1, unsigned intersectionID2);
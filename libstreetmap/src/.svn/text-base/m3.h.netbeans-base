#pragma once

#include <vector>
#include <string>
#include "StreetEdge.h"
#include "AStarFunctions.h"
#include "StreetEdge.h"


// Returns a path (route) between the start intersection and the end 
// intersection, if one exists. If no path exists, this routine returns 
// an empty (size == 0) vector. If more than one path exists, the path 
// with the shortest travel time is returned. The path is returned as a vector 
// of street segment ids; traversing these street segments, in the given order,
// would take one from the start to the end intersection.
std::vector<unsigned> find_path_between_intersections(unsigned 
                   intersect_id_start, unsigned intersect_id_end);

// Returns the time required to travel along the path specified. The path
// is passed in as a vector of street segment ids, and this function can 
// assume the vector either forms a legal path or has size == 0.
// The travel time is the sum of the length/speed-limit of each street 
// segment, plus 15 seconds per turn implied by the path. A turn occurs
// when two consecutive street segments have different street names.
double compute_path_travel_time(const std::vector<unsigned>& path);

// Returns the ID of the closest intersection to a POI
// used as a helper function for find_path_to_point_of_interest function
unsigned find_closest_intersection_from_POI (std::string desirePOIname);

// Returns the shortest travel time path (vector of street segments) from 
// the start intersection to a point of interest with the specified name.
// If no such path exists, returns an empty (size == 0) vector.
std::vector<unsigned> find_path_to_point_of_interest (unsigned 
                   intersect_id_start, std::string desired_point_of_interest_name);

// Returns the intersection ID for the inputted intersection name 
unsigned parse_intersection_name (string intersectionName);

void remove_whitespace(string& intersectionName);

vector<string> predictive_streets(string currentText, unsigned textNum);

vector<string> predictive_intersections(string currentText);

bool contains_and(string currentText);

vector<string> predictive_intersections(string currentText, unsigned textNum);

unsigned lazy_user_input (string currentText);

vector<string> predictive_POIs(string currentText, unsigned textNum);

void driving_directions(vector <unsigned> path, string start, string destination);

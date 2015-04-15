#pragma once

#include "graphics.h"
#include "m1.h"

#define PI 3.14159265
#define RAD_TO_DEGREE_MULTIPLIER 57.2957795131
#define DEGREE_TO_RAD_MULTIPLIER 0.01745329251
#define HIGH_SPEED_LIMIT 80
#define MED_SPEED_LIMIT 50

// Direction street is oriented in
// L = left, R = right, B = bottom, T = top
// e.g. LRBT = left to right, bottom to top => bottom left to top right
enum Direction {LR, RL, BT, TB, LRBT, LRTB, RLBT, RLTB};

// Draws lines representing street segments
void drawStreets();

// Draws the street names, angled collinearly with the street segment with the text
// centered to the segment.
void drawStreetNames(LatLon point1, LatLon point2, unsigned streetSegId);

void drawPath(vector<unsigned> path);     

// Draws a purple line with a circle at the end in the direction of the one way 
// street. The line begins at the beginning of the street segment and is collinear
// up to half way along the street segment.
void drawOneWay(LatLon point1, t_point center, float angle, Direction dir);
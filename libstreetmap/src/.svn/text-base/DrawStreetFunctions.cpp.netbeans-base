#include "DrawStreetFunctions.h"
#include "ButtonPressFunctions.h"

#include <math.h>
#include <vector>
#include <cmath>

// Global singleton class of map datastructures
extern MapDatabase *mapDatabase;
// Global variable to determine if one way street indicators are enabled 
extern bool oneWaysClicked;
// Prevent drawPath from consitently setting set visible world
bool zoomOnce = false;

// Draws lines representing street segments
void drawStreets() {
    unsigned numCurvePoints;
    
    // LatLon positions of curved points
    LatLon curveLatLon;
    LatLon prevCurvePoint;
    
    // x and y coordinates of each point
    double x1 = 0, x2 = 0, y1 = 0, y2 = 0;

    // IDs of the intersections at the two ends of a street segment.
    StreetSegmentEnds segmentEnds = {0, 0};
    unsigned fromInt = 0;
    unsigned toInt = 0;

    // point1 = "From" intersection
    // point2 = "To" intersection
    LatLon point1 = {0, 0};
    LatLon point2 = {0, 0};
    
    // Street segment begin and end LatLon position
    LatLon segmentBeginPoints = {0,0};
    LatLon segmentEndPoints = {0,0};
    
    // Street segment speed limit
    unsigned speedSize = 0;
    
    // Draw all street segments
    for (unsigned i = 0; i < getNumberOfStreetSegments(); i++) {
        // Get from and to intersection LatLon position
        segmentEnds = getStreetSegmentEnds(i);
        fromInt = segmentEnds.from;
        toInt = segmentEnds.to;
        
        point1 = getIntersectionPosition(fromInt);
        point2 = getIntersectionPosition(toInt);

        numCurvePoints = getStreetSegmentCurvePointCount(i);
        prevCurvePoint = point1;

        // Draw curved points
        for (unsigned j = 0; j < numCurvePoints; j++) {
            speedSize = getStreetSegmentSpeedLimit(i);
            
            // Draw streets differently depending on speed limit
            if (speedSize < MED_SPEED_LIMIT) {
                setlinewidth(1);
                setcolor(t_color(WHITE));
            } else if (speedSize < HIGH_SPEED_LIMIT) {
                setlinewidth(2);
                setcolor(t_color(YELLOW));
            } else {
                setlinewidth(3);
                setcolor(t_color(ORANGE));
            }

            curveLatLon = getStreetSegmentCurvePoint(i, j);
            
            drawline(prevCurvePoint.lon, prevCurvePoint.lat, curveLatLon.lon, curveLatLon.lat);

            segmentBeginPoints = {prevCurvePoint.lon, prevCurvePoint.lat};
            segmentEndPoints = {curveLatLon.lon, curveLatLon.lat};
            
            drawStreetNames(segmentBeginPoints, segmentEndPoints, i);
            
            prevCurvePoint = curveLatLon;
        }
        
        x1 = prevCurvePoint.lon;
        y1 = prevCurvePoint.lat;
        x2 = point2.lon;
        y2 = point2.lat;

        // Draw streets differently depending on speed limit
        if (speedSize < MED_SPEED_LIMIT) {
            setlinewidth(1);
            setcolor(t_color(WHITE));
        } else if (speedSize < HIGH_SPEED_LIMIT) {
            setlinewidth(2);
            setcolor(t_color(YELLOW));
        } else {
            setlinewidth(3);
            setcolor(t_color(ORANGE));
        }

        drawline(x1, y1, x2, y2);

        drawStreetNames(prevCurvePoint, point2, i);
    }
}

// Draws lines representing street segments
void drawPath(vector<unsigned> path) { 
    
    if (path.size() > 1 && zoomOnce == false) {
        
        /* Set the window to be zoomed in on the path */

        StreetSegmentEnds firstSegmentEnds, lastSegmentEnds;
        unsigned firstSeg_fromInt, firstSeg_toInt, lastSeg_fromInt, lastSeg_toInt;
        double firstSeg_x, lastSeg_x, firstSeg_y, lastSeg_y;
        LatLon begin_point, end_point;

        firstSegmentEnds = getStreetSegmentEnds(path[0]);
        firstSeg_fromInt = firstSegmentEnds.from;
        firstSeg_toInt = firstSegmentEnds.to;
        begin_point = getIntersectionPosition(firstSeg_fromInt);

        firstSeg_x = begin_point.lon;
        firstSeg_y = begin_point.lat;

        double minX = firstSeg_x;
        double maxX = firstSeg_x;
        double minY = firstSeg_y;
        double maxY = firstSeg_y;

        lastSegmentEnds = getStreetSegmentEnds(path.back());
        lastSeg_fromInt = lastSegmentEnds.from;
        lastSeg_toInt = lastSegmentEnds.to;

        begin_point = getIntersectionPosition(firstSeg_fromInt);
        end_point = getIntersectionPosition(lastSeg_toInt);

        firstSeg_x = begin_point.lon;
        firstSeg_y = begin_point.lat;
        lastSeg_x = end_point.lon;
        lastSeg_y = end_point.lat;

        if(firstSeg_x < minX)
            minX = firstSeg_x;
        if(lastSeg_x < minX)
            minX = lastSeg_x;
        if(firstSeg_y < minY)
            minY = firstSeg_y;
        if(lastSeg_y < minY)
            minY = lastSeg_y;

        if(firstSeg_x > maxX)
            maxX = firstSeg_x;
        if(lastSeg_x > maxX)
            maxX = lastSeg_x;
        if(firstSeg_y > maxY)
            maxY = firstSeg_y;
        if(lastSeg_y > maxY)
            maxY = lastSeg_y; 
        
        zoomOnce = true;
        
        set_visible_world (minX - 0.0007, minY - 0.0007, maxX + 0.0007, maxY + 0.0007);
        drawScreen();
    }

    setlinewidth(3);
    setcolor(0, 0, 204);
    
    unsigned numCurvePoints;
    
    // LatLon positions of curved points
    LatLon curveLatLon;
    LatLon prevCurvePoint;
    
    // x and y coordinates of each point
    double x1 = 0, x2 = 0, y1 = 0, y2 = 0;

    // IDs of the intersections at the two ends of a street segment.
    StreetSegmentEnds segmentEnds = {0, 0};
    unsigned fromInt = 0;
    unsigned toInt = 0;
    
    // point1 = "From" intersection
    // point2 = "To" intersection
    LatLon point1 = {0, 0};
    LatLon point2 = {0, 0};
    
    // Street segment begin and end LatLon position
    LatLon segmentBeginPoints = {0,0};
    LatLon segmentEndPoints = {0,0};
    
    unsigned segment;
    vector<unsigned> intersectionSegments;
    // Draw all street segments
    for (unsigned i = 0; i < path.size(); i++) {    
        segment = path[i];
        
        segmentEnds = getStreetSegmentEnds(segment);
        fromInt = segmentEnds.from;
        toInt = segmentEnds.to;
        
        point2 = getIntersectionPosition(toInt);
        point1 = getIntersectionPosition(fromInt);

        numCurvePoints = getStreetSegmentCurvePointCount(segment);
        prevCurvePoint = point1;

        // Draw curved points
        for (unsigned j = 0; j < numCurvePoints; j++) {
            curveLatLon = getStreetSegmentCurvePoint(segment, j);

            drawline(prevCurvePoint.lon, prevCurvePoint.lat, curveLatLon.lon, curveLatLon.lat);

            segmentBeginPoints = {prevCurvePoint.lon, prevCurvePoint.lat};
            segmentEndPoints = {curveLatLon.lon, curveLatLon.lat};

            prevCurvePoint = curveLatLon;
        }

        x1 = prevCurvePoint.lon;
        y1 = prevCurvePoint.lat;
        x2 = point2.lon;
        y2 = point2.lat;

        drawline(x1, y1, x2, y2);
    }
}

// Draws the street names, angled collinearly with the street segment with the text
// centered to the segment.
void drawStreetNames(LatLon point1, LatLon point2, unsigned streetSegId) {
    float angle;
    float x = 0;
    float y = 0;

    t_point center;
        
    Direction direction;
    
    setfontsize(8);
    
    // Determines the location of point 2 relative to point 1 and draws the street
    // name on an angle accordingly
    if (getStreetName(getStreetSegmentStreetID(streetSegId)) != "(unknown)") {
        // Where point 2 is relative to point 1
        // and determine the corresponding angle
        if (point2.lon > point1.lon) {
            if (point2.lat > point1.lat) {
                // point 2 is ABOVE and RIGHT of point 1
                x = point2.lon-point1.lon;
                y = point2.lat-point1.lat;
                angle = atan(y/x);
                center = {(float)point1.lon + (x/2),(float)point1.lat +  (y/2)};
                direction = LRBT; // Left to right, bottom to top (bottom left to top right)
            } else if (point2.lat < point1.lat) {
                // point 2 is BELOW and RIGHT of point 1
                x = point2.lon-point1.lon;
                y = point1.lat-point2.lat;
                angle = (2 * PI) - atan(y/x);
                center = {(float)point1.lon + (x/2), (float)point1.lat - (y/2)};
                direction = LRTB; // Left to right, top to bottom (top left to bottom right)
            }else {
                // point 2 is RIGHT of point 1
                angle = 0;
                center = {(float)point1.lon + (x/2), (float)point1.lat};
                direction = LR; // Left to right
            }
        } else if (point2.lon < point1.lon) { 
            if (point2.lat > point1.lat) {
                // point 2 is ABOVE and LEFT of point 1
                x = point1.lon-point2.lon;
                y = point2.lat-point1.lat;
                angle = (2 * PI) - atan(y/x);
                direction = RLBT; // Right to left, bottom to top (bottom right to top left)
                center = {(float)point2.lon + (x/2), (float)point2.lat - (y/2)};
            } else if (point2.lat < point1.lat) {
                // point 2 is BELOW and LEFT of point 1
                x = point1.lon-point2.lon;
                y = point1.lat-point2.lat;
                angle = atan(y/x);
                center = {(float)point2.lon + (x/2), (float)point2.lat + (y/2)};
                direction = RLTB; // Right to left, bottom to top (top right to bottom left)
            } else {
                // point 2 is LEFT of point 1
                angle = 0;
                center = {(float)point2.lon + (x/2),(float) point1.lat};
                direction = RL; // Right to left
            }
        } else {
            if (point2.lat > point1.lat) {
                // point 2 is DIRECTLY ABOVE point 1
                x = point2.lon - point1.lon;
                y = point2.lat - point1.lat;
                angle = PI / 2;
                center = {(float)point1.lon, (float)point1.lat + (y/2)};
                direction = BT; // Bottom to top
            } else {
                // point 2 is DIRECTLY BELOW point 1
                x = point2.lon - point1.lon;
                y = point1.lat - point2.lat;
                angle = PI / 2;
                center = {(float)point1.lon, (float)point1.lat + (y/2)};
                direction = TB; // Top to bottom
            }
        }

        // Draw the one way street indicator if the segment is one way and if 
        // the show one way streets button is clicked to be ON
        if (getStreetSegmentOneWay(streetSegId) && oneWaysClicked) {
            drawOneWay(point1, center, angle, direction);
        }
        
        setcolor(t_color(61, 61, 61)); // Grey
        
        // Set the rotation to computed angle
        angle *= RAD_TO_DEGREE_MULTIPLIER;
        settextrotation(angle);
        
        drawtext(center, getStreetName(getStreetSegmentStreetID(streetSegId)), x, y);
        
        settextrotation(0); // Reset the text rotation
    }
}

// Draws a purple line with a circle at the end in the direction of the one way 
// street. The line begins at the beginning of the street segment and is collinear
// up to half way along the street segment.
void drawOneWay(LatLon point1, t_point center, float angle, Direction dir) {
    setlinewidth(2);
    setcolor(t_color(150, 50, 250));

    // x and y offset from point1
    float xOffset, yOffset; 
    
    const float oneWayIndicatorRadius = 0.000006;
    
    // Depending on the direction of the street, calculate the begin and end points
    // of the line differently. The end at which the circle is drawn is also determined
    // by the street direction
    if (dir == LRBT) {  
        xOffset = center.x - point1.lon;
        yOffset = xOffset * tan(angle);
        drawline (point1.lon, point1.lat, point1.lon + xOffset, point1.lat + yOffset);
        fillarc(point1.lon + xOffset, point1.lat + yOffset, oneWayIndicatorRadius, 0, 360);
    } else if (dir == LRTB) {
        xOffset = center.x - point1.lon;
        angle = 2*PI - angle;
        yOffset = xOffset * tan(angle);
        drawline (point1.lon, point1.lat, point1.lon + xOffset, point1.lat - yOffset);
        fillarc(point1.lon + xOffset, point1.lat - yOffset, oneWayIndicatorRadius, 0, 360);
    } else if (dir == RLBT) {
        xOffset = point1.lon - center.x;
        angle = 2*PI - angle;
        yOffset = xOffset * tan(angle);
        drawline (point1.lon, point1.lat, point1.lon - xOffset, point1.lat + yOffset);
        fillarc(point1.lon - xOffset, point1.lat + yOffset, oneWayIndicatorRadius, 0, 360);
    } else if (dir == RLTB) {
        xOffset = point1.lon - center.x;
        yOffset = xOffset * tan(angle);
        drawline (point1.lon, point1.lat, point1.lon - xOffset, point1.lat - yOffset);
        fillarc(point1.lon - xOffset, point1.lat - yOffset, oneWayIndicatorRadius, 0, 360);
    } 
}
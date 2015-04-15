#pragma once

#include "graphics.h"

#define POI_MARKER_RADIUS 0.00003

// Enum for types of POI
enum POI_type {COFFEE, BANK, FOOD, CHURCH, PHARMACY, HEALTH, OTHER};

// Draws a symbol for each POI
void drawPOI();

// Returns POI_type (from enum list) of the point of interest
POI_type getPOIType(unsigned POI_id);

// Draws a brown cup to indicate coffee shops
void drawPOI_coffeeShop(t_point coordinates);
// Draws a yellow dollar sign to indicate banks
void drawPOI_bank(t_point coordinates);
// Draws an orange spoon and fork to indicate restaurant / food joints
void drawPOI_food(t_point coordinates);
// Draws a white cross to indicate churches
void drawPOI_church(t_point coordinates);
// Draws Rx logo to indicate pharmacies and drug stores
void drawPOI_pharmacy(t_point coordinates);
// Draws red cross to indicate health centers
void drawPOI_health(t_point coordinates);
// Draws a black dot for other POIs
void drawPOI_other(t_point coordinates);
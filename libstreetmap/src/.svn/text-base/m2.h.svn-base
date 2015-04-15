#pragma once

#include "MapDatabase.h"
#include "DrawStreetFunctions.h"
#include "DrawFeaturesFunctions.h"
#include "DrawPOIFunctions.h"
#include "ButtonPressFunctions.h"

// Draws the map whose at map_path; this should be a .bin file.
void draw_map(std::string map_path);

// Called in main.cpp
void drawScreen();

//************************** USER INPUT FUNCTIONS ******************************//
// Draws a red pin on map where mouse clicked
void act_on_button_press (float x, float y, t_event_buttonPressed event);
// POIs with names starting with character are shown
void act_on_key_press (char c);
// POIs names are shown when hovered over
void act_on_mouse_move (float x, float y);

// Function to draw the red pin on mouse click
void drawPinDrops();

void drawSearchBar();

void drawHelpScreen();
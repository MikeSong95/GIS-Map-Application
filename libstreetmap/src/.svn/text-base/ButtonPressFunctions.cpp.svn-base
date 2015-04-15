#include "ButtonPressFunctions.h"

#include <vector>
#include <list>

using namespace std;

// Global variables to indicate which POIs are to be drawn
// Initialized as true so all are initially drawn
bool allPOIsClicked = true,
        coffeeClicked = true, 
        bankClicked = true, 
        foodClicked = true,
        churchClicked = true,
        pharmaClicked = true,
        healthClicked = true,
        otherPOIsClicked = true,
        oneWaysClicked = true,
        searchClicked = false,
        helpClicked = false;
        
// Draws all POIs when button is pressed
void allPOIs_buttonFnc(void (*drawscreen) (void)) {
    (void) drawscreen; // suppress unused warning
    if (allPOIsClicked){
        allPOIsClicked = false;
        coffeeClicked = false, 
        bankClicked = false, 
        foodClicked = false,
        churchClicked = false,
        pharmaClicked = false,
        healthClicked = false,
        otherPOIsClicked = false;
        change_button_text("POIs ON", "POIs OFF");
        change_button_text("Cafes ON", "Cafes OFF");
        change_button_text("Banks ON", "Banks OFF");
        change_button_text("Food ON", "Food OFF");
        change_button_text("Churches ON", "Churches OFF");
        change_button_text("Pharmacy ON", "Pharmacy OFF");
        change_button_text("Medical ON", "Medical OFF");
        change_button_text("Others ON", "Others OFF");
        drawScreen();
    } else {
        allPOIsClicked = true;
        coffeeClicked = true, 
        bankClicked = true, 
        foodClicked = true,
        churchClicked = true,
        pharmaClicked = true,
        healthClicked = true,
        otherPOIsClicked = true;
        change_button_text("POIs OFF", "POIs ON");
        change_button_text("Cafes OFF", "Cafes ON");
        change_button_text("Banks OFF", "Banks ON");
        change_button_text("Food OFF", "Food ON");
        change_button_text("Churches OFF", "Churches ON");
        change_button_text("Pharmacy OFF", "Pharmacy ON");
        change_button_text("Medical OFF", "Medical ON");
        change_button_text("Others OFF", "Others ON");
        drawScreen();
    }
}

// Draws the Coffee Shops POIs when its Button is pressed
void coffeeShops_buttonFnc(void (*drawscreen) (void)) {
    (void) drawscreen; // suppress unused warning
    if (coffeeClicked){
        coffeeClicked = false;
        change_button_text("Cafes ON", "Cafes OFF");
        drawScreen();
    } else {
        coffeeClicked = true;
        change_button_text("Cafes OFF", "Cafes ON");
        drawScreen();
    }
}

// Draws the Banks when its Button is pressed
void banks_buttonFnc(void (*drawscreen) (void)) {
    (void) drawscreen; // suppress unused warning
    if (bankClicked){
        bankClicked = false;
        change_button_text("Banks ON", "Banks OFF");
        drawScreen();
    } else {
        bankClicked = true;
        change_button_text("Banks OFF", "Banks ON");
        drawScreen();
    }
}

// Draws the Food Restaurants when its Button is pressed
void food_buttonFnc(void (*drawscreen) (void)) {
    (void) drawscreen; // suppress unused warning
    if (foodClicked){
        foodClicked = false;
        change_button_text("Food ON", "Food OFF");
        drawScreen();
    } else {
        foodClicked = true;
        change_button_text("Food OFF", "Food ON");
        drawScreen();
    }
}

// Draws the Churches when its Button is pressed
void churches_buttonFnc(void (*drawscreen) (void)) {
    (void) drawscreen; // suppress unused warning
    if (churchClicked){
        churchClicked = false;
        change_button_text("Churches ON", "Churches OFF");
        drawScreen();
    } else {
        churchClicked = true;
        change_button_text("Churches OFF", "Churches ON");
        drawScreen();
    }
}

// Draws the Pharmacies when its Button is pressed
void pharmacies_buttonFnc(void (*drawscreen) (void)) {
    (void) drawscreen; // suppress unused warning
    if (pharmaClicked){
        pharmaClicked = false;
        change_button_text("Pharmacy ON", "Pharmacy OFF");
        drawScreen();
    } else {
        pharmaClicked = true;
        change_button_text("Pharmacy OFF", "Pharmacy ON");
        drawScreen();
    }
}

// Draws the Health Care locations when its Button is pressed
void healthCare_buttonFnc(void (*drawscreen) (void)) {
    (void) drawscreen; // suppress unused warning
    if (healthClicked){
        healthClicked = false;
        change_button_text("Medical ON", "Medical OFF");
        drawScreen();
    } else {
        healthClicked = true;
        change_button_text("Medical OFF", "Medical ON");
        drawScreen();
    }
}

// Draws the POIs that do not fit in categories listed above 
void otherPOIs_buttonFnc(void (*drawscreen) (void)) {
    (void) drawscreen; // suppress unused warning
    if (otherPOIsClicked){
        otherPOIsClicked = false;
        change_button_text("Others ON", "Others OFF");
        drawScreen();
    } else {
        otherPOIsClicked = true;
        change_button_text("Others OFF", "Others ON");
        drawScreen();
    }
}

// Removes selected Pin locations when button is clicked
extern vector<LatLon> pinDropPoints;
extern vector<LatLon> noIntersectionsPinDropPoints;
void pinDrop_buttonFnc(void (*drawscreen) (void)){
    pinDropPoints.clear();
    noIntersectionsPinDropPoints.clear();
    drawScreen();
}

// Draws the one way street symbols 
void oneWays_buttonFnc(void (*drawscreen) (void)) {
    (void) drawscreen; // suppress unused warning
    if (oneWaysClicked){
        oneWaysClicked = false;
        change_button_text("One Ways ON", "One Ways OFF");
        drawScreen();
    } else {
        oneWaysClicked = true;
        change_button_text("One Ways OFF", "One Ways ON");
        drawScreen();
    }
}


void search_buttonFnc(void (*drawscreen) (void)){
    (void) drawscreen; // suppress unused warning
    if (searchClicked){
        searchClicked = false;
        change_button_text("Search ON", "Search OFF");
        drawScreen();
    } else {
        searchClicked = true;
        change_button_text("Search OFF", "Search ON");
        drawScreen();
    }
}

void help_buttonFnc(void (*drawscreen) (void)) {
    (void) drawscreen; // suppress unused warning
    if (helpClicked) {
        helpClicked = false;
        change_button_text("Help ON", "Help OFF");
        drawScreen();
    } else {
        helpClicked = true;
        change_button_text("Help OFF", "Help ON");
        drawScreen();
    }
}

// Determines if a POI type is to be displayed or not based on if the corresponding
// button is ON or OFF.
bool isClicked (POI_type type) {
    if (type == COFFEE) {
        return coffeeClicked;
    } else if (type == BANK) {
        return bankClicked;
    } else if (type == FOOD) {
        return foodClicked;
    } else if (type == CHURCH) {
        return churchClicked;
    } else if (type == PHARMACY) {
        return pharmaClicked;
    } else if (type == HEALTH) {
        return healthClicked;
    } else if (type == OTHER) {
        return otherPOIsClicked;
    } else { // Return false if nothing has been defined
        return false;
    }
}
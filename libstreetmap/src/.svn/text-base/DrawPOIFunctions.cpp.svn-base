#include "DrawPOIFunctions.h"
#include "MapDatabase.h"
#include "ButtonPressFunctions.h"

// Global singleton class of data structures declared in m1.cpp
extern MapDatabase* mapDatabase;

extern bool allPOIsClicked,
                coffeeClicked, 
                bankClicked,
                foodClicked,
                churchClicked,
                pharmaClicked,
                healthClicked,
                otherPOIsClicked,
                searchClicked;

// Draws a symbol for each POI
void drawPOI() {
    t_point POI_coordinates; // x and y coordinates of POI
    POI_type type;
    
    // Iterate through each POI to draw
    for (auto iter = mapDatabase->POI_beginIter(); iter != mapDatabase->POI_endIter(); iter++) {
        POI_coordinates.x = iter->second.lon;
        POI_coordinates.y = iter->second.lat;
        setcolor(t_color(220, 85, 85));
        
        // Get the type of point of interest (type from enum POI_type)
        type = getPOIType(iter->first);
        
        // Draw different symbols depending on POI_type
        switch(type) {
            case POI_type::COFFEE : drawPOI_coffeeShop(POI_coordinates); break;
            case POI_type::BANK : drawPOI_bank(POI_coordinates); break;
            case POI_type::FOOD : drawPOI_food(POI_coordinates); break;
            case POI_type::CHURCH : drawPOI_church(POI_coordinates); break;
            case POI_type::PHARMACY : drawPOI_pharmacy(POI_coordinates); break;
            case POI_type::HEALTH : drawPOI_health(POI_coordinates); break;
            default : drawPOI_other(POI_coordinates);
        }

        setcolor(t_color(0, 0, 0)); // Reset color
    }
}

// Returns POI_type (from enum list) of the point of interest
POI_type getPOIType(unsigned POI_id){
    string POI_name = getPointOfInterestName(POI_id);
    
   /*Coffee Shops*/
    if (POI_name.find("Tim Hortons", 0) != std::string::npos || 
            POI_name.find("Second Cup", 0) != std::string::npos ||
            POI_name.find("Coffee") != std::string::npos ||
            POI_name.find("Cafe") != std::string::npos ||
            POI_name.find("Espresso") != std::string::npos ||
            POI_name.find("Tea") != std::string::npos ||
            POI_name.find("Starbucks") != std::string::npos){
        return COFFEE;
    } 
    /*Banks*/
    else if (POI_name.find("TD", 0) != std::string::npos || 
            POI_name.find("BMO", 0) != std::string::npos ||
            POI_name.find("RBC", 0) != std::string::npos ||
            POI_name.find("CIBC") != std::string::npos ||
            POI_name.compare("Scotiabank") == 0 ||  // Scotiabank Theatre not a bank
            POI_name.find("HSBC") != std::string::npos ||
            POI_name.find("Bank") != std::string::npos ||
            POI_name.find("Credit Union") != std::string::npos){
        return BANK;
    } 
    /*Food*/
    else if (POI_name.find("Pizza", 0) != std::string::npos || 
            POI_name.find("Restaurant", 0) != std::string::npos ||
            POI_name.find("Subway") != std::string::npos ||
            POI_name.find("McDonald's") != std::string::npos || 
            POI_name.find("Harvey's") != std::string::npos ||
            POI_name.find("Wendy's") != std::string::npos ||
            POI_name.find("Bistro") != std::string::npos || 
            POI_name.find("Grill") != std::string::npos ||
            POI_name.find("Burger") != std::string::npos || 
            POI_name.find("Kitchen") != std::string::npos ||
            POI_name.find("Sushi") != std::string::npos ||
            POI_name.find("Pub") != std::string::npos || 
            POI_name.find("Deli") != std::string::npos ||
            POI_name.find("Sandwiches") != std::string::npos||
            POI_name.find("Bakery") != std::string::npos ||
            POI_name.find("Pastries") != std::string::npos ||
            POI_name.find("Wok") != std::string::npos||
            POI_name.find("Teriyaki") != std::string::npos ||
            POI_name.find("Food") != std::string::npos ||
            POI_name.find("Cuisine") != std::string::npos ||
            POI_name.find("Diner") != std::string::npos ||
            POI_name.find("Steakhouse") != std::string::npos ||
            POI_name.find("Eatery") != std::string::npos ||
            POI_name.find("Swiss Chalet") != std::string::npos ||
            POI_name.find("Yogurt") != std::string::npos ||
            POI_name.find("Gelato") != std::string::npos ||
            POI_name.find("Sub") != std::string::npos ||
            POI_name.find("Poutinery") != std::string::npos ||
            POI_name.find("Burrito") != std::string::npos ||
            POI_name.find("Quizno's") != std::string::npos ||
            POI_name.find("Moxie's") != std::string::npos ||
            POI_name.find("Tavern") != std::string::npos ||
            POI_name.find("Sandwich") != std::string::npos ||
            POI_name.find("Fries") != std::string::npos ){
        return FOOD;
    } 
    /*Church*/
    else if (POI_name.find("Baptismal", 0) != std::string::npos || 
            POI_name.find("Chapel", 0) != std::string::npos ||
            POI_name.find("Christ") != std::string::npos ||
            POI_name.find("Jesus") != std::string::npos || 
            POI_name.find("God") != std::string::npos ||
            POI_name.find("Christian") != std::string::npos ||
            POI_name.find("Temple") != std::string::npos || 
            POI_name.find("Presbyterian") != std::string::npos ||
            POI_name.find("Pentecostal") != std::string::npos || 
            POI_name.find("Budist") != std::string::npos ||
            POI_name.find("Budism") != std::string::npos ||
            POI_name.find("Worship") != std::string::npos ||
            POI_name.find("Baptist") != std::string::npos ||
            POI_name.find("Church") != std::string::npos ||
            POI_name.find("Parish") != std::string::npos){
        return CHURCH;
    } 
    /*Pharmacy*/
    else if (POI_name.find("Pharmacy", 0) != std::string::npos || 
            POI_name.find("Drug", 0) != std::string::npos ||
            POI_name.find("Drugs") != std::string::npos ||
            POI_name.find("Pharmaceutical") != std::string::npos || 
            POI_name.find("Pharmaceuticals") != std::string::npos ||
            POI_name.find("Rexall") != std::string::npos ||
            POI_name.find("I.D.A") != std::string::npos || 
            POI_name.find("Pharmacies") != std::string::npos ||
            POI_name.find("Pharmasave") != std::string::npos){
        return PHARMACY;
    } 
    /*Hospitals and such*/
    else if (POI_name.find("Hospital", 0) != std::string::npos || 
            POI_name.find("Health", 0) != std::string::npos ||
            POI_name.find("Doctor") != std::string::npos ||
            POI_name.find("Healthy") != std::string::npos || 
            POI_name.find("Medical") != std::string::npos ||
            POI_name.find("Medicine") != std::string::npos ||
            POI_name.find("Clinic") != std::string::npos || 
            POI_name.find("Dental") != std::string::npos ||
            POI_name.find("Dentist") != std::string::npos ||
            POI_name.find("Orthodontist") != std::string::npos ||
            POI_name.find("Orthodontics") != std::string::npos || 
            POI_name.find("Oral") != std::string::npos || 
            POI_name.find("Surgeon") != std::string::npos ||
            POI_name.find("Physician") != std::string::npos){
        return HEALTH;
    } 
    /*Other*/
    else {
        return OTHER;
    }
}

/** NOTE: "Magic Numbers" have been precisely selected to make accurate pictures **/

// Draws a brown cup to indicate coffee shops
void drawPOI_coffeeShop(t_point coordinates) {
    if (coffeeClicked){
        setcolor(t_color(153, 76, 0));  // Brown
        fillrect(coordinates.x - 0.00003, coordinates.y + 0.00003, coordinates.x + 0.00001, coordinates.y - 0.00004); // Cup
        drawarc(coordinates.x, coordinates.y - 0.000006, 0.000021, 270, 180); // Handle
    }
}

// Draws a yellow dollar sign to indicate banks
void drawPOI_bank(t_point coordinates) {
    if(bankClicked){
        setcolor(t_color(255, 255, 0)); // Yellow
        // Top half of S
        drawellipticarc(coordinates.x + 0.000011, coordinates.y + 0.000006, 0.000030, 0.000016, 75, 195);
        // Bottom half of S
        drawellipticarc(coordinates.x - 0.000011, coordinates.y - 0.000022, 0.000033, 0.000016, 260, 190);
        // Left vertical line
        drawline (coordinates.x - 0.000007, coordinates.y - 0.00005, coordinates.x - 0.000007, coordinates.y + 0.000035);
        // Right vertical line
        drawline(coordinates.x + 0.00001, coordinates.y - 0.00005, coordinates.x + 0.00001, coordinates.y + 0.000035);
    }
}

// Draws an orange spoon and fork to indicate restaurant / food joints
void drawPOI_food(t_point coordinates) {
    
    if (foodClicked){
        setcolor(t_color(255, 128, 0)); // Orange
        // Spoon
        drawline (coordinates.x - 0.00001, coordinates.y - 0.00004, coordinates.x - 0.00001, coordinates.y + 0.00002);
        fillellipticarc(coordinates.x - 0.00001f, coordinates.y + 0.000027f, 0.000008, 0.000015, 0, 360);
        // Fork
        drawline (coordinates.x + 0.000013, coordinates.y - 0.00004, coordinates.x + 0.000013, coordinates.y + 0.00002);
        fillellipticarc(coordinates.x + 0.000013, coordinates.y + 0.00002, 0.00001, 0.000008, 180, 180);
        // Fork tines
        drawline (coordinates.x + 0.000006, coordinates.y + 0.00002, coordinates.x + 0.000006, coordinates.y + 0.00004);
        drawline (coordinates.x + 0.000013, coordinates.y + 0.00002, coordinates.x + 0.000013, coordinates.y + 0.00004);
        drawline (coordinates.x + 0.000026, coordinates.y + 0.00002, coordinates.x + 0.000026, coordinates.y + 0.00004);
    }
}

// Draws a purple cross to indicate places of worship
void drawPOI_church(t_point coordinates){
    if (churchClicked){
        setcolor(t_color(204, 0, 102)); // Purple
        fillrect(coordinates.x - 0.00001, coordinates.y + 0.00003, coordinates.x + 0.00001, coordinates.y - 0.00004);
        fillrect(coordinates.x - 0.00002, coordinates.y + 0.000014, coordinates.x + 0.00002, coordinates.y - 0.000003);
    }
}

// Draws Rx to indicate pharmacy
void drawPOI_pharmacy(t_point coordinates){
    
    if (pharmaClicked){
        setcolor(t_color(0, 0, 255));   // Blue
        drawline (coordinates.x - 0.00001, coordinates.y - 0.000035, coordinates.x - 0.00001, coordinates.y + 0.000035);
        drawellipticarc(coordinates.x - 0.00001, coordinates.y + 0.000015, 0.000035, 0.00002, 270, 180);
        drawline (coordinates.x + 0.000007, coordinates.y - 0.0000019, coordinates.x + 0.000045, coordinates.y - 0.000045);
        drawline (coordinates.x + 0.000015, coordinates.y - 0.000045, coordinates.x + 0.000045, coordinates.y - 0.00001);
    }
}

// Draws a red cross to indicate health centers
void drawPOI_health(t_point coordinates){
    
    if (healthClicked){
        setcolor(t_color(255, 0, 0));
        fillrect(coordinates.x - 0.000011, coordinates.y + 0.00003, coordinates.x + 0.000011, coordinates.y - 0.00004);
        fillrect(coordinates.x - 0.00002, coordinates.y + 0.000009, coordinates.x + 0.000023, coordinates.y - 0.000011);
    }
}

// Draws a black circle with black square inside for other POIs
void drawPOI_other(t_point coordinates) {
    
    if (otherPOIsClicked){
        setcolor(t_color(0, 0, 0));
        drawarc(coordinates.x, coordinates.y, POI_MARKER_RADIUS, 0, 360);
        fillrect(coordinates.x - 0.000005, coordinates.y - 0.000008, coordinates.x + 0.000005, coordinates.y + 0.000008);
    }
}
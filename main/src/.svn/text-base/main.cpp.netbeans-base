#include <iostream>
#include <list>
#include <vector>
#include <readline/readline.h>
#include <readline/history.h>

#include "m1.h"
#include "m2.h"
#include "UserInput.h"
#include "AStarFunctions.h"
#include "graphics.h"
#include "easygl_constants.h"
#include "m3.h"

using namespace std;

extern MapDatabase* mapDatabase;

int main() {     
    string userIn;      // User text input
    string mapToLoad;   // Which map to load

    const char* mapSelectionPrompt = "Enter the city or region you would like to load: ";

    while (1){  
        string userIn;      // User text input
        string mapToLoad;   // Which map to load
        
        // Determine which city to load    
        userIn = string(acceptUserInput(mapSelectionPrompt));
        mapToLoad = selectMap(userIn);
                
        if (mapToLoad != "invalid") {
            load_map("/cad2/ece297s/public/maps/"+mapToLoad);        
            init_graphics("City Map", t_color(192,192,192)); // light grey background

            double x1, x2, y1, y2;
            StreetSegmentEnds segmentEnds;
            unsigned fromInt;
            unsigned toInt;
            LatLon point1, point2;

            /*The following algorithm is used to frame the map during the initial load:
             The first street segment end is used to initialize the variables holding values for
             lowest and highest x and y values. Next, the for loop compares the LatLon values of 
             all of the street segment ends to determine the bounds for the entire city. */

            segmentEnds = getStreetSegmentEnds(0);
            fromInt = segmentEnds.from;
            toInt = segmentEnds.to;
            point1 = getIntersectionPosition(fromInt);
            x1 = point1.lon;
            y1 = point1.lat;

            double minX = x1;
            double maxX = x1;
            double minY = y1;
            double maxY = y1;

            // Find the absolute LatLon values to position the entire city within interface
            for (unsigned i= 0; i < getNumberOfStreetSegments(); i++){
                segmentEnds = getStreetSegmentEnds(i);
                fromInt = segmentEnds.from;
                toInt = segmentEnds.to;

                point1 = getIntersectionPosition(fromInt);
                point2 = getIntersectionPosition(toInt);

                x1 = point1.lon;
                y1 = point1.lat;
                x2 = point2.lon;
                y2 = point2.lat;

                if(x1 < minX)
                    minX = x1;
                if(x2 < minX)
                    minX = x2;
                if(y1 < minY)
                    minY = y1;
                if(y2 < minY)
                    minY = y2;

                if(x1 > maxX)
                    maxX = x1;
                if(x2 > maxX)
                    maxX = x2;
                if(y1 > maxY)
                    maxY = y1;
                if(y2 > maxY)
                    maxY = y2; 
            }
            
            set_mouse_move_input("on");
            set_keypress_input("on");
            set_visible_world (minX, minY, maxX, maxY);
            
            // Makes filter buttons
            create_button("Load New Map", "POIs ON",allPOIs_buttonFnc);
            create_button("POIs ON", "Cafes ON",coffeeShops_buttonFnc);
            create_button("Cafes ON", "Banks ON",banks_buttonFnc);
            create_button("Banks ON", "Food ON",food_buttonFnc);
            create_button("Food ON", "Churches ON",churches_buttonFnc);
            create_button("Churches ON", "Pharmacy ON",pharmacies_buttonFnc);
            create_button("Pharmacy ON", "Medical ON",healthCare_buttonFnc);
            create_button("Medical ON", "Others ON",otherPOIs_buttonFnc);
            create_button("Others ON", "Clear Pins",pinDrop_buttonFnc);
            create_button("Clear Pins", "One Ways ON",oneWays_buttonFnc);
            create_button("One Ways ON", "Search OFF",search_buttonFnc);
            create_button("Search OFF", "Help OFF", help_buttonFnc);
            
            event_loop(act_on_button_press, act_on_mouse_move, act_on_key_press, drawScreen);
            
        } else {
            cout << "City Not Found" << endl;
        }

        close_graphics();
        close_map();
        
        mapDatabase = MapDatabase::getSingletonPointer();     
    }
    
    return 0;
}

// BELOW IS FOR PARSING THE .BIN FILE ONLY
/*
string weWantThis = "emergency"; // change this to parse
    
for (unsigned i = 0; i < getFeatureCount(); i++) {
    if (getFeatureAttribute(i, weWantThis) != "") {
        cout << "There are " << weWantThis << " features! Implement them." << endl;
        cout << getFeatureAttribute(i, weWantThis) << endl;
    }
}
*/

/*
// THIS IS TO CHECK WHAT FEATURE IDs CORRESPOND TO WHAT FEATURE ATTRIBUTES
string weWantThis = "leisure";
for (unsigned i = 0; i < getFeatureCount(); i++) {
    if (getFeatureAttribute(i, weWantThis) != "") {
        cout << "Feature ID: " << i << " . Feature Category: " << weWantThis << endl;
        cout << getFeatureAttribute(i, weWantThis) << endl;
    }
}
*/


/*
// THIS IS TO GET THE STREET NAME OF WHICH A STREET SEGMENT ID IS PART
for (unsigned i = 0; i < getNumberOfStreetSegments(); i++) {
                        
    unsigned streetID = getStreetSegmentStreetID(i);
    string streetName = getStreetName(streetID);
                
    cout << "Street Segment ID: " << i << " is part of Street Name: " << streetName << endl;
}
*/


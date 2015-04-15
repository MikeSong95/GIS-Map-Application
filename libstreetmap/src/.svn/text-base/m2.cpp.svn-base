#include "m2.h" 
#include "m3.h"
#include "m4.h"

#define POI_RADIUS 0.00001
#define VERTICAL_TEXT_OFFSET 0.00005f

#define ERROR_VALUE 999999999

using namespace std;
extern bool searchClicked, helpClicked;

bool textInput1Clicked = false; 
bool textInput2Clicked = false;

bool suggestionBoxes1 = false;
bool suggestionBoxes2 = false; 

bool checkBox1Clicked = false;
bool checkBox2Clicked = true; 

string intersectionInput1 = "";
string intersectionInput2 = "";
vector<unsigned> path = {0};

// Global singleton class of data structures declared in m1.cpp
extern MapDatabase* mapDatabase;
extern vector<string> suggestionsText1;
extern vector<string> suggestionsText2;
// Keep track of where "pin" locations are
vector<LatLon> pinDropPoints;
vector<LatLon> noIntersectionsPinDropPoints;
extern bool zoomOnce;

void draw_map(std::string map_path) {
    // Not to be implemented
}

void drawScreen() {
    
    suggestionBoxes1 = false;
    suggestionBoxes2 = false;
    clearscreen();
    
    drawFeatures();
    drawStreets();
    drawPath(path); 
    drawPOI();
    drawPinDrops();
    drawSearchBar();
    
    drawHelpScreen();
}

//************************** USER INPUT FUNCTIONS ******************************//

// Draws a red pin on map where mouse clicked
void act_on_button_press (float x, float y, t_event_buttonPressed event){ 
    LatLon intersection_goal_pos;
    LatLon intersection_start_pos;
    
    float xLow;
    float yLow;
    float xHigh;
    float yHigh;   
    float yLow2;
    float yHigh2;
    
    float xLowest = 0;
    float yLowest = 0;
    float xHighest = 0;
    float yHighest = 0;
    
    float xPathLowest = 0;
    float yPathLowest = 0;
    float xPathHighest = 0;
    float yPathHighest = 0;
    
    t_point bottomLeft1;
    t_point topright1;
    t_point bottomLeft2;
    t_point topright2; 
    
    float xtextBoxLow = 0;
    float ytextBoxLow = 0;
    float xtextBoxHigh = 0;
    float ytextBoxHigh = 0;
    
    float topBoxY = 0;
    float secondBoxY = 0;
    float thirdBoxY = 0;
    float fourthBoxY = 0;
    float fifthBoxY = 0;
    
    // Initialize bounds for checkBox
    float minCheckBox1X = 0;
    float minCheckBox1Y = 0;
    float maxCheckBox1X = 0;
    float maxCheckBox1Y = 0;
    
    float minCheckBox2X = 0;
    float minCheckBox2Y = 0;
    float maxCheckBox2X = 0;
    float maxCheckBox2Y = 0;
    
    t_bound_box visibleWorld = get_visible_world();
    float xLeft = visibleWorld.left();   
    float yTop = visibleWorld.top();
    
    float width = visibleWorld.get_width();
    float height = visibleWorld.get_height();
    float heightBox = 0;
    
    // clears error message at bottom of screen to erase previous error message (if any)
    update_message("");
    
    if (searchClicked){
        xLeft = visibleWorld.left();          
        yTop = visibleWorld.top();

        width = visibleWorld.get_width();
        height = visibleWorld.get_height();

        xLow = xLeft + width*1/20;
        yLow = yTop - height*1/12;
        xHigh = xLeft + width*3/5;
        yHigh = yTop - height*1/20; 
        
        heightBox = yTop - height*1/20 - (yTop - height*1/12);
        
        yHigh2 = yTop - height*1/11;
        yLow2 = yTop - height*1/11 - heightBox;
        
        xLowest = xLeft + width*1/20;
        yLowest = yTop - height*1/11 - heightBox - heightBox;
        xHighest = xLeft + width*3/5;
        yHighest = yTop - height*1/20 + heightBox;
        
        bottomLeft1 = {xLow,yLow};
        topright1 = {xHigh,yHigh};
        bottomLeft2 = {xLow,yLow2};
        topright2 = {xHigh,yHigh2};
        
        xPathLowest = xLeft + width/2;
        yPathLowest = yTop - height*1/11 - heightBox - heightBox;
        xPathHighest = xLeft + width*3/5;
        yPathHighest = yTop - height*1/10 - heightBox;
        
        xtextBoxLow = xLeft + width*1/20;
        ytextBoxLow = yTop - height*1/11 - 7*heightBox;
        xtextBoxHigh = xLeft + width*3/5;
        ytextBoxHigh = yTop - height*1/11 - 2*heightBox;
        
        topBoxY = yTop - height*1/11 - 2*heightBox;
        secondBoxY = yTop - height*1/11 - 3*heightBox;
        thirdBoxY = yTop - height*1/11 - 4*heightBox;
        fourthBoxY = yTop - height*1/11 - 5*heightBox;
        fifthBoxY = yTop - height*1/11 - 6*heightBox;
        
        minCheckBox1X = xLeft + width*21/100;
        minCheckBox1Y = yTop - height*1/11 - heightBox - heightBox;
        maxCheckBox1X = xLeft + width*24/100;
        maxCheckBox1Y = yTop - height*1/10 - heightBox;
    
        minCheckBox2X = xLeft + width*32/100;
        minCheckBox2Y = yTop - height*1/11 - heightBox - heightBox;
        maxCheckBox2X = xLeft + width*35/100;
        maxCheckBox2Y = yTop - height*1/10 - heightBox;
    }

    if (searchClicked && x>= xLow && x <= xHigh && y>= yLow && y<= yHigh){
        textInput1Clicked = true;
        textInput2Clicked = false;
        
        if (intersectionInput1.back() != '|')
            intersectionInput1 = intersectionInput1 + "|";
        
        if (intersectionInput2.size() >= 1 && intersectionInput2[intersectionInput2.size() - 1] == '|')
            intersectionInput2.erase(intersectionInput2.end() - 1);
        
        setcolor (t_color (255, 255, 255));
        fillrect(bottomLeft2, topright2);
        
        setcolor (t_color (0, 0, 0));
        drawtext_in(t_bound_box(bottomLeft2,topright2), intersectionInput2);
        
        setcolor (t_color (255, 255, 255));
        fillrect(bottomLeft1, topright1);
        
        setcolor (t_color (0, 0, 0));
        drawtext_in(t_bound_box(bottomLeft1,topright1), intersectionInput1);
        
    }else if (searchClicked && x>= xLow && x <= xHigh && y>= yLow2 && y<= yHigh2){ 
        textInput1Clicked = false;
        textInput2Clicked = true; 
        
        if (intersectionInput2.back() != '|')
            intersectionInput2 = intersectionInput2 + "|";
        
        if (intersectionInput1.size() >= 1 && intersectionInput1[intersectionInput1.size() - 1] == '|')
            intersectionInput1.erase(intersectionInput1.end() - 1);
        
        setcolor (t_color (255, 255, 255));
        fillrect(bottomLeft1, topright1);
        
        setcolor (t_color (0, 0, 0));
        drawtext_in( t_bound_box(bottomLeft1,topright1), intersectionInput1);
        
        setcolor (t_color (255, 255, 255));
        fillrect(bottomLeft2, topright2);
        
        setcolor (t_color (0, 0, 0));
        drawtext_in( t_bound_box(bottomLeft2,topright2), intersectionInput2);

        
    }else if (searchClicked && x>= xPathLowest && x <= xPathHighest && y>= yPathLowest && y<= yPathHighest){
        
        // Find Path box clicked on interface 
        
        if (intersectionInput1.size() >= 1 && intersectionInput1[intersectionInput1.size() - 1] == '|')
            intersectionInput1.erase(intersectionInput1.end() - 1);
        
        if (intersectionInput2.size() >= 1 && intersectionInput2[intersectionInput2.size() - 1] == '|')
            intersectionInput2.erase(intersectionInput2.end() - 1);
        
        unsigned intersectionID1 = parse_intersection_name(intersectionInput1);
        unsigned intersectionID2 = parse_intersection_name(intersectionInput2);
        
        path.clear();
        if (checkBox2Clicked)
            path = AStarAlgorithm(intersectionID1, intersectionID2);
        else 
            path = find_path_to_point_of_interest(intersectionID1, intersectionInput2);
        
        float start_x, start_y, goal_x, goal_y;
        
        // invalid path
        if (path.size() == 0) {
            update_message("INVALID PATH, please try again.");
        }
        
        // invalid intersection
        else if (path[0] == ERROR_VALUE) {
            update_message("INVALID INPUT, please try again.");
        }
        
        // path and intersections valid
        else {
            intersection_start_pos = getIntersectionPosition(intersectionID1);
          
           if (checkBox2Clicked){
                intersection_goal_pos = getIntersectionPosition(intersectionID2);
           }else {
                intersection_goal_pos = getIntersectionPosition(getStreetSegmentEnds(path.back()).to);
           }
            
            start_x = intersection_start_pos.lon;  
            start_y = intersection_start_pos.lat;
            goal_x = intersection_goal_pos.lon;
            goal_y = intersection_goal_pos.lat;
            
            // Remove the previous intersection pin drops
            pinDropPoints = noIntersectionsPinDropPoints;
            
            // Push new start and goal intersections onto pinDropPoints vector
            pinDropPoints.push_back({start_x, start_y});
            pinDropPoints.push_back({goal_x, goal_y});
            
            // New path, so zoom in to it
            zoomOnce = false;
            
            // When drawScreen() is called, it will draw the path as well as the pin drops
            drawScreen(); 
        }
        
        if (path[0] != ERROR_VALUE)
            driving_directions(path, intersectionInput1, intersectionInput2);

        textInput1Clicked = false;
        textInput2Clicked = false; 
        
        // Empty text boxes after search
        intersectionInput1 = "";
        intersectionInput2 = "";
                
        setcolor (t_color (255, 255, 255));
        fillrect(bottomLeft1, topright1);
        
        setcolor (t_color (0, 0, 0));
        drawtext_in( t_bound_box(bottomLeft1,topright1), intersectionInput1);
        
        setcolor (t_color (255, 255, 255));
        fillrect(bottomLeft2, topright2);
        
        setcolor (t_color (0, 0, 0));
        drawtext_in( t_bound_box(bottomLeft2,topright2), intersectionInput2);
        
    }else if (searchClicked && suggestionBoxes1 && x>= xtextBoxLow && x <= xtextBoxHigh && y>= ytextBoxLow && y<= ytextBoxHigh){
    
        if (y>= secondBoxY  && y<= topBoxY){
            intersectionInput1 = suggestionsText1[0];
        }else if (y>= thirdBoxY && y<= secondBoxY){
            intersectionInput1 = suggestionsText1[1];
        }else if (y>= fourthBoxY && y<= thirdBoxY){
            intersectionInput1 = suggestionsText1[2];;
        }else if (y>= fifthBoxY && y<= fourthBoxY){
            intersectionInput1 = suggestionsText1[3];;
        }else{
            intersectionInput1 = suggestionsText1[4];;
        }
        
        setcolor (t_color (255, 255, 255));
        fillrect(bottomLeft1, topright1);
        
        setcolor (t_color (0, 0, 0));
        drawtext_in( t_bound_box(bottomLeft1,topright1), intersectionInput1); 
 
    }else if (searchClicked && suggestionBoxes2 && x>= xtextBoxLow && x <= xtextBoxHigh && y>= ytextBoxLow && y<= ytextBoxHigh){
        
        if (y>= secondBoxY  && y<= topBoxY){
            intersectionInput2 = suggestionsText2[0];
        }else if (y>= thirdBoxY && y<= secondBoxY){
            intersectionInput2 = suggestionsText2[1];
        }else if (y>= fourthBoxY && y<= thirdBoxY){
            intersectionInput2 = suggestionsText2[2];
        }else if (y>= fifthBoxY && y<= fourthBoxY){
            intersectionInput2 = suggestionsText2[3];
        }else{
            intersectionInput2 = suggestionsText2[4];
        }
        
        setcolor (t_color (255, 255, 255));
        fillrect(bottomLeft2, topright2);
        
        setcolor (t_color (0, 0, 0));
        drawtext_in( t_bound_box(bottomLeft2,topright2), intersectionInput2);
  
    }else if (searchClicked && x>= minCheckBox1X && x <= maxCheckBox1X && y>= minCheckBox1Y && y<= maxCheckBox1Y){
    
        checkBox1Clicked = true;
        checkBox2Clicked = false; 
        
        setcolor (t_color (0, 0, 0));
        drawline(xLeft + width*21/100,yTop - height*1/11 - heightBox - heightBox,xLeft + width*24/100,yTop - height*1/10 - heightBox);
        drawline(xLeft + width*21/100,yTop - height*1/10 - heightBox,xLeft + width*24/100,yTop - height*1/11 - heightBox - heightBox);
        setcolor (t_color (255, 255, 255));
        fillrect({xLeft + width*32/100, yTop - height*1/11 - heightBox - heightBox},{xLeft + width*35/100, yTop - height*1/10 - heightBox});
        

    }else if (searchClicked && x>= minCheckBox2X && x <= maxCheckBox2X && y>= minCheckBox2Y && y<= maxCheckBox2Y){
    
        checkBox1Clicked = false;
        checkBox2Clicked = true;
        
        setcolor (t_color (0, 0, 0));
        drawline(xLeft + width*32/100,yTop - height*1/11 - heightBox - heightBox,xLeft + width*35/100,yTop - height*1/10 - heightBox);
        drawline(xLeft + width*32/100,yTop - height*1/10 - heightBox,xLeft + width*35/100,yTop - height*1/11 - heightBox - heightBox);
        setcolor (t_color (255, 255, 255));
        fillrect({xLeft + width*21/100, yTop - height*1/11 - heightBox - heightBox},{xLeft + width*24/100, yTop - height*1/10 - heightBox});
        
    }else if (searchClicked && x>= xLowest && x <= xHighest && y>= yLowest && y<= yHighest){
        
        textInput1Clicked = false;
        textInput2Clicked = false; 
        
        // inside box but not on anything in particular 
        if (intersectionInput1.size() >= 1 && intersectionInput1[intersectionInput1.size() - 1] == '|')
            intersectionInput1.erase(intersectionInput1.end() - 1);
        
        if (intersectionInput2.size() >= 1 && intersectionInput2[intersectionInput2.size() - 1] == '|')
            intersectionInput2.erase(intersectionInput2.end() - 1);
        
        setcolor (t_color (255, 255, 255));
        fillrect(bottomLeft1, topright1);
        
        setcolor (t_color (0, 0, 0));
        drawtext_in( t_bound_box(bottomLeft1,topright1), intersectionInput1);
        
        setcolor (t_color (255, 255, 255));
        fillrect(bottomLeft2, topright2);
        
        setcolor (t_color (0, 0, 0));
        drawtext_in( t_bound_box(bottomLeft2,topright2), intersectionInput2);
          
    }else {
        
        // Drop Pin on the Map
        
        textInput1Clicked = false; 
        textInput2Clicked = false;
        
        if (intersectionInput1.size() >= 1 && intersectionInput1[intersectionInput1.size() - 1] == '|')
            intersectionInput1.erase(intersectionInput1.end() - 1);
        
        if (intersectionInput2.size() >= 1 && intersectionInput2[intersectionInput2.size() - 1] == '|')
            intersectionInput2.erase(intersectionInput2.end() - 1);

        flushinput();
        pinDropPoints.push_back({x,y});
        noIntersectionsPinDropPoints.push_back({x,y});
        drawScreen();
    }    
}

// POIs with names starting with character are shown
void act_on_key_press (char character) {
    
    int numChar = int(character);
    bool okInput = isprint(numChar); 
    
    if (textInput1Clicked){
        
        flushinput();
        t_bound_box visibleWorld = get_visible_world();
        float xLeft = visibleWorld.left();          
        float yTop = visibleWorld.top();

        float width = visibleWorld.get_width();
        float height = visibleWorld.get_height();
        
        t_point bottomLeft = {xLeft + width*1/20, yTop - height*1/12};
        t_point upperRight = {xLeft + width*3/5, yTop - height*1/20};  
        
        if (intersectionInput1.size() >= 1 && intersectionInput1[intersectionInput1.size() -1] != '|')
            intersectionInput1 = intersectionInput1 + "|";
        
        if (intersectionInput2.size() >= 1 && intersectionInput2[intersectionInput2.size() -1] != '|')
            intersectionInput2 = intersectionInput2 + "|";

        if (character == '\b'){
            if (intersectionInput1.size() >= 2)
                intersectionInput1.erase(intersectionInput1.end() - 2);
            
        }else{     
            
            if (okInput){
                if (intersectionInput1.size() >= 1 && intersectionInput1[intersectionInput1.size() - 1] == '|')
                    intersectionInput1.erase(intersectionInput1.end() - 1);

                intersectionInput1 = intersectionInput1 + character + "|";
            }
        }
            
        setcolor (t_color (255, 255, 255));
        fillrect(bottomLeft, upperRight);
        
        setcolor (t_color (0, 0, 0));
        drawtext_in( t_bound_box(bottomLeft,upperRight), intersectionInput1);
  
        
        vector<string> predictions;
        
        if (contains_and(intersectionInput1))
            predictions = predictive_intersections(intersectionInput1, 1);
        else 
            predictions = predictive_streets(intersectionInput1, 1);
        
        flushinput();
        
        if (intersectionInput1.size() > 4 && predictions.size() >= 1){
            
            // Showing text #1 suggestions, turn off #2's suggestions
            suggestionBoxes1 = true;
            suggestionBoxes2 = false;
            
            float heightBox = yTop - height*1/20 - (yTop - height*1/12);

            t_point bottomLeftFirstText = {xLeft + width*1/20,yTop - height*1/11 - 3*heightBox};
            t_point topRightFirstText = {xLeft + width*3/5,yTop - height*1/11 - 2*heightBox};

            setcolor (t_color (255, 255, 255));
            fillrect(bottomLeftFirstText, topRightFirstText);

            setcolor (t_color (0, 0, 255));
            drawtext_in( t_bound_box(bottomLeftFirstText,topRightFirstText), predictions[0]);
            
            setcolor (t_color (150, 200, 255));
            t_point firstLine = {xLeft + width*1/20,yTop - height*1/11 - 3*heightBox};
            t_point secondLine = {xLeft + width*3/5,yTop - height*1/11 - 3*heightBox};
        
            drawline(firstLine, secondLine);

        }
        
        if (intersectionInput1.size() > 4 && predictions.size() >= 2){
            float heightBox = yTop - height*1/20 - (yTop - height*1/12);

            t_point bottomLeftFirstText = {xLeft + width*1/20,yTop - height*1/11 - 4*heightBox};
            t_point topRightFirstText = {xLeft + width*3/5,yTop - height*1/11 - 3*heightBox};

            setcolor (t_color (255, 255, 255));
            fillrect(bottomLeftFirstText, topRightFirstText);

            setcolor (t_color (0, 0, 255));
            drawtext_in( t_bound_box(bottomLeftFirstText,topRightFirstText), predictions[1]);
            
            setcolor (t_color (150, 200, 255));
            t_point firstLine = {xLeft + width*1/20,yTop - height*1/11 - 4*heightBox};
            t_point secondLine = {xLeft + width*3/5,yTop - height*1/11 - 4*heightBox};
        
            drawline(firstLine, secondLine);
        }
        
        if (intersectionInput1.size() > 4 && predictions.size() >= 3){
            float heightBox = yTop - height*1/20 - (yTop - height*1/12);

            t_point bottomLeftFirstText = {xLeft + width*1/20,yTop - height*1/11 - 5*heightBox};
            t_point topRightFirstText = {xLeft + width*3/5,yTop - height*1/11 - 4*heightBox};

            setcolor (t_color (255, 255, 255));
            fillrect(bottomLeftFirstText, topRightFirstText);

            setcolor (t_color (0, 0, 255));
            drawtext_in( t_bound_box(bottomLeftFirstText,topRightFirstText), predictions[2]);
            
            setcolor (t_color (150, 200, 255));
            t_point firstLine = {xLeft + width*1/20,yTop - height*1/11 - 5*heightBox};
            t_point secondLine = {xLeft + width*3/5,yTop - height*1/11 - 5*heightBox};
        
            drawline(firstLine, secondLine);  
        }
        
        if (intersectionInput1.size() > 4 && predictions.size() >= 4){
            float heightBox = yTop - height*1/20 - (yTop - height*1/12);

            t_point bottomLeftFirstText = {xLeft + width*1/20,yTop - height*1/11 - 6*heightBox};
            t_point topRightFirstText = {xLeft + width*3/5,yTop - height*1/11 - 5*heightBox};

            setcolor (t_color (255, 255, 255));
            fillrect(bottomLeftFirstText, topRightFirstText);

            setcolor (t_color (0, 0, 255));
            drawtext_in( t_bound_box(bottomLeftFirstText,topRightFirstText), predictions[3]);
            
            setcolor (t_color (150, 200, 255));
            t_point firstLine = {xLeft + width*1/20,yTop - height*1/11 - 6*heightBox};
            t_point secondLine = {xLeft + width*3/5,yTop - height*1/11 - 6*heightBox};
        
            drawline(firstLine, secondLine);
        }
        
        if (intersectionInput1.size() > 4 && predictions.size() >= 5){
            float heightBox = yTop - height*1/20 - (yTop - height*1/12);

            t_point bottomLeftFirstText = {xLeft + width*1/20,yTop - height*1/11 - 7*heightBox};
            t_point topRightFirstText = {xLeft + width*3/5,yTop - height*1/11 - 6*heightBox};

            setcolor (t_color (255, 255, 255));
            fillrect(bottomLeftFirstText, topRightFirstText);

            setcolor (t_color (0, 0, 255));
            drawtext_in( t_bound_box(bottomLeftFirstText,topRightFirstText), predictions[4]);
            
            setcolor (t_color (150, 200, 255));
            t_point firstLine = {xLeft + width*1/20,yTop - height*1/11 - 7*heightBox};
            t_point secondLine = {xLeft + width*3/5,yTop - height*1/11 - 7*heightBox};
        
            drawline(firstLine, secondLine);
        }
    }else if (textInput2Clicked){
    
        flushinput();
        t_bound_box visibleWorld = get_visible_world();
        float xLeft = visibleWorld.left();          
        float yTop = visibleWorld.top();

        float width = visibleWorld.get_width();
        float height = visibleWorld.get_height();
        float heightBox = yTop - height*1/20 - (yTop - height*1/12);
        
        t_point bottomLeft = {xLeft + width*1/20, yTop - height*1/11 - heightBox};
        t_point upperRight = {xLeft + width*3/5, yTop - height*1/11};  
       
        if (character == '\b'){
            if (intersectionInput2.size() >= 2)
                intersectionInput2.erase(intersectionInput2.end() - 2);
            
        }else{
            
            if (okInput){
                if (intersectionInput2.size() >= 1 && intersectionInput2[intersectionInput2.size() - 1] == '|')
                    intersectionInput2.erase(intersectionInput2.end() - 1);

                intersectionInput2 = intersectionInput2 + character + "|";
            }
        }

        setcolor (t_color (255, 255, 255));
        fillrect(bottomLeft, upperRight);
        
        setcolor (t_color (0, 0, 0));
        drawtext_in( t_bound_box(bottomLeft,upperRight), intersectionInput2);
        
        vector<string> predictions;
        
        if (contains_and(intersectionInput2) && checkBox2Clicked)
            predictions = predictive_intersections(intersectionInput2, 2);
        else if (checkBox2Clicked)
            predictions = predictive_streets(intersectionInput2, 2);
        else
            predictions = predictive_POIs(intersectionInput2, 2);
        
        flushinput();
        
        if (intersectionInput2.size() > 4 && predictions.size() >= 1){
            
            // Showing text #2 suggestions, turn off #1's suggestions
            suggestionBoxes2 = true; 
            suggestionBoxes1 = false;
            
            float heightBox = yTop - height*1/20 - (yTop - height*1/12);

            t_point bottomLeftFirstText = {xLeft + width*1/20,yTop - height*1/11 - 3*heightBox};
            t_point topRightFirstText = {xLeft + width*3/5,yTop - height*1/11 - 2*heightBox};

            setcolor (t_color (255, 255, 255));
            fillrect(bottomLeftFirstText, topRightFirstText);

            setcolor (t_color (0, 0, 255));
            drawtext_in( t_bound_box(bottomLeftFirstText,topRightFirstText), predictions[0]);
            
            setcolor (t_color (150, 200, 255));
            t_point firstLine = {xLeft + width*1/20,yTop - height*1/11 - 3*heightBox};
            t_point secondLine = {xLeft + width*3/5,yTop - height*1/11 - 3*heightBox};
        
            drawline(firstLine, secondLine);
        }
        
        if (intersectionInput2.size() > 4 && predictions.size() >= 2){
            float heightBox = yTop - height*1/20 - (yTop - height*1/12);

            t_point bottomLeftFirstText = {xLeft + width*1/20,yTop - height*1/11 - 4*heightBox};
            t_point topRightFirstText = {xLeft + width*3/5,yTop - height*1/11 - 3*heightBox};

            setcolor (t_color (255, 255, 255));
            fillrect(bottomLeftFirstText, topRightFirstText);

            setcolor (t_color (0, 0, 255));
            drawtext_in( t_bound_box(bottomLeftFirstText,topRightFirstText), predictions[1]);
            
            setcolor (t_color (150, 200, 255));
            t_point firstLine = {xLeft + width*1/20,yTop - height*1/11 - 4*heightBox};
            t_point secondLine = {xLeft + width*3/5,yTop - height*1/11 - 4*heightBox};
        
            drawline(firstLine, secondLine);
            
        }
        
        if (intersectionInput2.size() > 4 && predictions.size() >= 3){
            float heightBox = yTop - height*1/20 - (yTop - height*1/12);

            t_point bottomLeftFirstText = {xLeft + width*1/20,yTop - height*1/11 - 5*heightBox};
            t_point topRightFirstText = {xLeft + width*3/5,yTop - height*1/11 - 4*heightBox};

            setcolor (t_color (255, 255, 255));
            fillrect(bottomLeftFirstText, topRightFirstText);

            setcolor (t_color (0, 0, 255));
            drawtext_in( t_bound_box(bottomLeftFirstText,topRightFirstText), predictions[2]);
            
            setcolor (t_color (150, 200, 255));
            t_point firstLine = {xLeft + width*1/20,yTop - height*1/11 - 5*heightBox};
            t_point secondLine = {xLeft + width*3/5,yTop - height*1/11 - 5*heightBox};
        
            drawline(firstLine, secondLine);
        }
        
        if (intersectionInput2.size() > 4 && predictions.size() >= 4){
            float heightBox = yTop - height*1/20 - (yTop - height*1/12);

            t_point bottomLeftFirstText = {xLeft + width*1/20,yTop - height*1/11 - 6*heightBox};
            t_point topRightFirstText = {xLeft + width*3/5,yTop - height*1/11 - 5*heightBox};

            setcolor (t_color (255, 255, 255));
            fillrect(bottomLeftFirstText, topRightFirstText);

            setcolor (t_color (0, 0, 255));
            drawtext_in( t_bound_box(bottomLeftFirstText,topRightFirstText), predictions[3]);
            
            setcolor (t_color (150, 200, 255));
            t_point firstLine = {xLeft + width*1/20,yTop - height*1/11 - 6*heightBox};
            t_point secondLine = {xLeft + width*3/5,yTop - height*1/11 - 6*heightBox};
        
            drawline(firstLine, secondLine);
        }
        
        if (intersectionInput2.size() > 4 && predictions.size() >= 5){
            float heightBox = yTop - height*1/20 - (yTop - height*1/12);

            t_point bottomLeftFirstText = {xLeft + width*1/20,yTop - height*1/11 - 7*heightBox};
            t_point topRightFirstText = {xLeft + width*3/5,yTop - height*1/11 - 6*heightBox};

            setcolor (t_color (255, 255, 255));
            fillrect(bottomLeftFirstText, topRightFirstText);

            setcolor (t_color (0, 0, 255));
            drawtext_in( t_bound_box(bottomLeftFirstText,topRightFirstText), predictions[4]);
            
            setcolor (t_color (150, 200, 255));
            t_point firstLine = {xLeft + width*1/20,yTop - height*1/11 - 7*heightBox};
            t_point secondLine = {xLeft + width*3/5,yTop - height*1/11 - 7*heightBox};
        
            drawline(firstLine, secondLine);
        }      
    }else {
        flushinput();

        LatLon location;
        float x, y;

        for (auto iter = mapDatabase->POI_beginIter(); iter != mapDatabase->POI_endIter(); iter++){

            if (getPointOfInterestName((iter->first))[0] == character){
                location = getPointOfInterestPosition((iter->first));
                x = location.lat;  
                y = location.lon;
                setcolor(0, 0, 255); // Blue
                drawtext({y,(x + VERTICAL_TEXT_OFFSET)}, getPointOfInterestName((iter->first)), find_street_segment_length(iter->first), find_street_segment_length(iter->first));           
            }
        }
    } 
}

// POIs names are shown when hovered over
// POI names will NOT appear if button has disabled POI from displaying
void act_on_mouse_move(float y, float x) {
    flushinput();
    
    t_bound_box visibleWorld = get_visible_world();

    float xLeft = visibleWorld.left();          
    float yTop = visibleWorld.top();

    float width = visibleWorld.get_width();
    float height = visibleWorld.get_height();

    float heightBox = yTop - height*1/20 - (yTop - height*1/12);
    
    float xtextBoxLow = xLeft + width*1/20;
    float ytextBoxLow = yTop - height*1/11 - 7*heightBox;
    float xtextBoxHigh = xLeft + width*3/5;
    float ytextBoxHigh = yTop - height*1/11 - 2*heightBox;
    
    float topBoxY = yTop - height*1/11 - 2*heightBox;
    float secondBoxY = yTop - height*1/11 - 3*heightBox;
    float thirdBoxY = yTop - height*1/11 - 4*heightBox;
    float fourthBoxY = yTop - height*1/11 - 5*heightBox;
    float fifthBoxY = yTop - height*1/11 - 6*heightBox;
    float bottomBoxY = yTop - height*1/11 - 7*heightBox;
    
    if (searchClicked && suggestionBoxes1 && y>= xtextBoxLow && y <= xtextBoxHigh && x>= ytextBoxLow && x<= ytextBoxHigh){

        if (x>= secondBoxY  && x<= topBoxY){
            
            //Make first box yellow and the rest white
            setcolor (t_color (255, 255, 150));
            fillrect({xtextBoxLow,secondBoxY}, {xtextBoxHigh,topBoxY});
            setcolor (t_color (0, 0, 255));
            drawtext_in( t_bound_box({xtextBoxLow,secondBoxY},{xtextBoxHigh,topBoxY}), suggestionsText1[0]);

            setcolor (t_color (255, 255, 255));
            fillrect({xtextBoxLow,thirdBoxY}, {xtextBoxHigh,secondBoxY});
            setcolor (t_color (0, 0, 255));
            drawtext_in( t_bound_box({xtextBoxLow,thirdBoxY},{xtextBoxHigh,secondBoxY}), suggestionsText1[1]);

            setcolor (t_color (255, 255, 255));
            fillrect({xtextBoxLow,fourthBoxY}, {xtextBoxHigh,thirdBoxY});
            setcolor (t_color (0, 0, 255));
            drawtext_in( t_bound_box({xtextBoxLow,fourthBoxY},{xtextBoxHigh,thirdBoxY}), suggestionsText1[2]);

            setcolor (t_color (255, 255, 255));
            fillrect({xtextBoxLow,fifthBoxY}, {xtextBoxHigh,fourthBoxY});
            setcolor (t_color (0, 0, 255));
            drawtext_in( t_bound_box({xtextBoxLow,fifthBoxY},{xtextBoxHigh,fourthBoxY}), suggestionsText1[3]);

            setcolor (t_color (255, 255, 255));
            fillrect({xtextBoxLow,bottomBoxY}, {xtextBoxHigh,fifthBoxY});
            setcolor (t_color (0, 0, 255));
            drawtext_in( t_bound_box({xtextBoxLow,bottomBoxY},{xtextBoxHigh,fifthBoxY}), suggestionsText1[4]);

            setcolor (t_color (150, 200, 255)); 
            drawline({xtextBoxLow,secondBoxY}, {xtextBoxHigh,secondBoxY});
            drawline({xtextBoxLow,thirdBoxY}, {xtextBoxHigh,thirdBoxY});
            drawline({xtextBoxLow,fourthBoxY}, {xtextBoxHigh,fourthBoxY});
            drawline({xtextBoxLow,fifthBoxY}, {xtextBoxHigh,fifthBoxY});
            drawline({xtextBoxLow,bottomBoxY}, {xtextBoxHigh,bottomBoxY});
            
            
        }else if (x>= thirdBoxY && x<= secondBoxY){
            
            //Make second box yellow and the rest white
            setcolor (t_color (255, 255, 255));
            fillrect({xtextBoxLow,secondBoxY}, {xtextBoxHigh,topBoxY});
            setcolor (t_color (0, 0, 255));
            drawtext_in( t_bound_box({xtextBoxLow,secondBoxY},{xtextBoxHigh,topBoxY}), suggestionsText1[0]);

            setcolor (t_color (255, 255, 150));
            fillrect({xtextBoxLow,thirdBoxY}, {xtextBoxHigh,secondBoxY});
            setcolor (t_color (0, 0, 255));
            drawtext_in( t_bound_box({xtextBoxLow,thirdBoxY},{xtextBoxHigh,secondBoxY}), suggestionsText1[1]);

            setcolor (t_color (255, 255, 255));
            fillrect({xtextBoxLow,fourthBoxY}, {xtextBoxHigh,thirdBoxY});
            setcolor (t_color (0, 0, 255));
            drawtext_in( t_bound_box({xtextBoxLow,fourthBoxY},{xtextBoxHigh,thirdBoxY}), suggestionsText1[2]);

            setcolor (t_color (255, 255, 255));
            fillrect({xtextBoxLow,fifthBoxY}, {xtextBoxHigh,fourthBoxY});
            setcolor (t_color (0, 0, 255));
            drawtext_in( t_bound_box({xtextBoxLow,fifthBoxY},{xtextBoxHigh,fourthBoxY}), suggestionsText1[3]);

            setcolor (t_color (255, 255, 255));
            fillrect({xtextBoxLow,bottomBoxY}, {xtextBoxHigh,fifthBoxY});
            setcolor (t_color (0, 0, 255));
            drawtext_in( t_bound_box({xtextBoxLow,bottomBoxY},{xtextBoxHigh,fifthBoxY}), suggestionsText1[4]);

            setcolor (t_color (150, 200, 255)); 
            drawline({xtextBoxLow,secondBoxY}, {xtextBoxHigh,secondBoxY});
            drawline({xtextBoxLow,thirdBoxY}, {xtextBoxHigh,thirdBoxY});
            drawline({xtextBoxLow,fourthBoxY}, {xtextBoxHigh,fourthBoxY});
            drawline({xtextBoxLow,fifthBoxY}, {xtextBoxHigh,fifthBoxY});
            drawline({xtextBoxLow,bottomBoxY}, {xtextBoxHigh,bottomBoxY});
            
        }else if (x>= fourthBoxY && x<= thirdBoxY){
           
            //Make third box yellow and the rest white
            setcolor (t_color (255, 255, 255));
            fillrect({xtextBoxLow,secondBoxY}, {xtextBoxHigh,topBoxY});
            setcolor (t_color (0, 0, 255));
            drawtext_in( t_bound_box({xtextBoxLow,secondBoxY},{xtextBoxHigh,topBoxY}), suggestionsText1[0]);

            setcolor (t_color (255, 255, 255));
            fillrect({xtextBoxLow,thirdBoxY}, {xtextBoxHigh,secondBoxY});
            setcolor (t_color (0, 0, 255));
            drawtext_in( t_bound_box({xtextBoxLow,thirdBoxY},{xtextBoxHigh,secondBoxY}), suggestionsText1[1]);

            setcolor (t_color (255, 255, 150));
            fillrect({xtextBoxLow,fourthBoxY}, {xtextBoxHigh,thirdBoxY});
            setcolor (t_color (0, 0, 255));
            drawtext_in( t_bound_box({xtextBoxLow,fourthBoxY},{xtextBoxHigh,thirdBoxY}), suggestionsText1[2]);

            setcolor (t_color (255, 255, 255));
            fillrect({xtextBoxLow,fifthBoxY}, {xtextBoxHigh,fourthBoxY});
            setcolor (t_color (0, 0, 255));
            drawtext_in( t_bound_box({xtextBoxLow,fifthBoxY},{xtextBoxHigh,fourthBoxY}), suggestionsText1[3]);

            setcolor (t_color (255, 255, 255));
            fillrect({xtextBoxLow,bottomBoxY}, {xtextBoxHigh,fifthBoxY});
            setcolor (t_color (0, 0, 255));
            drawtext_in( t_bound_box({xtextBoxLow,bottomBoxY},{xtextBoxHigh,fifthBoxY}), suggestionsText1[4]);

            setcolor (t_color (150, 200, 255)); 
            drawline({xtextBoxLow,secondBoxY}, {xtextBoxHigh,secondBoxY});
            drawline({xtextBoxLow,thirdBoxY}, {xtextBoxHigh,thirdBoxY});
            drawline({xtextBoxLow,fourthBoxY}, {xtextBoxHigh,fourthBoxY});
            drawline({xtextBoxLow,fifthBoxY}, {xtextBoxHigh,fifthBoxY});
            drawline({xtextBoxLow,bottomBoxY}, {xtextBoxHigh,bottomBoxY});
            
        }else if (x>= fifthBoxY && x<= fourthBoxY){
            
            //Make fourth box yellow and the rest white
            setcolor (t_color (255, 255, 255));
            fillrect({xtextBoxLow,secondBoxY}, {xtextBoxHigh,topBoxY});
            setcolor (t_color (0, 0, 255));
            drawtext_in( t_bound_box({xtextBoxLow,secondBoxY},{xtextBoxHigh,topBoxY}), suggestionsText1[0]);

            setcolor (t_color (255, 255, 255));
            fillrect({xtextBoxLow,thirdBoxY}, {xtextBoxHigh,secondBoxY});
            setcolor (t_color (0, 0, 255));
            drawtext_in( t_bound_box({xtextBoxLow,thirdBoxY},{xtextBoxHigh,secondBoxY}), suggestionsText1[1]);

            setcolor (t_color (255, 255, 255));
            fillrect({xtextBoxLow,fourthBoxY}, {xtextBoxHigh,thirdBoxY});
            setcolor (t_color (0, 0, 255));
            drawtext_in( t_bound_box({xtextBoxLow,fourthBoxY},{xtextBoxHigh,thirdBoxY}), suggestionsText1[2]);

            setcolor (t_color (255, 255, 150));
            fillrect({xtextBoxLow,fifthBoxY}, {xtextBoxHigh,fourthBoxY});
            setcolor (t_color (0, 0, 255));
            drawtext_in( t_bound_box({xtextBoxLow,fifthBoxY},{xtextBoxHigh,fourthBoxY}), suggestionsText1[3]);

            setcolor (t_color (255, 255, 255));
            fillrect({xtextBoxLow,bottomBoxY}, {xtextBoxHigh,fifthBoxY});
            setcolor (t_color (0, 0, 255));
            drawtext_in( t_bound_box({xtextBoxLow,bottomBoxY},{xtextBoxHigh,fifthBoxY}), suggestionsText1[4]);

            setcolor (t_color (150, 200, 255)); 
            drawline({xtextBoxLow,secondBoxY}, {xtextBoxHigh,secondBoxY});
            drawline({xtextBoxLow,thirdBoxY}, {xtextBoxHigh,thirdBoxY});
            drawline({xtextBoxLow,fourthBoxY}, {xtextBoxHigh,fourthBoxY});
            drawline({xtextBoxLow,fifthBoxY}, {xtextBoxHigh,fifthBoxY});
            drawline({xtextBoxLow,bottomBoxY}, {xtextBoxHigh,bottomBoxY});
            
        }else{
            
            //Make fifth box yellow and the rest white
            setcolor (t_color (255, 255, 255));
            fillrect({xtextBoxLow,secondBoxY}, {xtextBoxHigh,topBoxY});
            setcolor (t_color (0, 0, 255));
            drawtext_in( t_bound_box({xtextBoxLow,secondBoxY},{xtextBoxHigh,topBoxY}), suggestionsText1[0]);

            setcolor (t_color (255, 255, 255));
            fillrect({xtextBoxLow,thirdBoxY}, {xtextBoxHigh,secondBoxY});
            setcolor (t_color (0, 0, 255));
            drawtext_in( t_bound_box({xtextBoxLow,thirdBoxY},{xtextBoxHigh,secondBoxY}), suggestionsText1[1]);

            setcolor (t_color (255, 255, 255));
            fillrect({xtextBoxLow,fourthBoxY}, {xtextBoxHigh,thirdBoxY});
            setcolor (t_color (0, 0, 255));
            drawtext_in( t_bound_box({xtextBoxLow,fourthBoxY},{xtextBoxHigh,thirdBoxY}), suggestionsText1[2]);

            setcolor (t_color (255, 255, 255));
            fillrect({xtextBoxLow,fifthBoxY}, {xtextBoxHigh,fourthBoxY});
            setcolor (t_color (0, 0, 255));
            drawtext_in( t_bound_box({xtextBoxLow,fifthBoxY},{xtextBoxHigh,fourthBoxY}), suggestionsText1[3]);

            setcolor (t_color (255, 255, 150));
            fillrect({xtextBoxLow,bottomBoxY}, {xtextBoxHigh,fifthBoxY});
            setcolor (t_color (0, 0, 255));
            drawtext_in( t_bound_box({xtextBoxLow,bottomBoxY},{xtextBoxHigh,fifthBoxY}), suggestionsText1[4]);

            setcolor (t_color (150, 200, 255)); 
            drawline({xtextBoxLow,secondBoxY}, {xtextBoxHigh,secondBoxY});
            drawline({xtextBoxLow,thirdBoxY}, {xtextBoxHigh,thirdBoxY});
            drawline({xtextBoxLow,fourthBoxY}, {xtextBoxHigh,fourthBoxY});
            drawline({xtextBoxLow,fifthBoxY}, {xtextBoxHigh,fifthBoxY});
            drawline({xtextBoxLow,bottomBoxY}, {xtextBoxHigh,bottomBoxY});
            
        }

    // Hovering inside second text box suggestion list 
    }else if (searchClicked && suggestionBoxes2 && y>= xtextBoxLow && y <= xtextBoxHigh && x>= ytextBoxLow && x<= ytextBoxHigh){
    
        if (x>= secondBoxY  && x<= topBoxY){
            
            //Make first box yellow and the rest white
            setcolor (t_color (255, 255, 150));
            fillrect({xtextBoxLow,secondBoxY}, {xtextBoxHigh,topBoxY});
            setcolor (t_color (0, 0, 255));
            drawtext_in( t_bound_box({xtextBoxLow,secondBoxY},{xtextBoxHigh,topBoxY}), suggestionsText2[0]);

            setcolor (t_color (255, 255, 255));
            fillrect({xtextBoxLow,thirdBoxY}, {xtextBoxHigh,secondBoxY});
            setcolor (t_color (0, 0, 255));
            drawtext_in( t_bound_box({xtextBoxLow,thirdBoxY},{xtextBoxHigh,secondBoxY}), suggestionsText2[1]);

            setcolor (t_color (255, 255, 255));
            fillrect({xtextBoxLow,fourthBoxY}, {xtextBoxHigh,thirdBoxY});
            setcolor (t_color (0, 0, 255));
            drawtext_in( t_bound_box({xtextBoxLow,fourthBoxY},{xtextBoxHigh,thirdBoxY}), suggestionsText2[2]);

            setcolor (t_color (255, 255, 255));
            fillrect({xtextBoxLow,fifthBoxY}, {xtextBoxHigh,fourthBoxY});
            setcolor (t_color (0, 0, 255));
            drawtext_in( t_bound_box({xtextBoxLow,fifthBoxY},{xtextBoxHigh,fourthBoxY}), suggestionsText2[3]);

            setcolor (t_color (255, 255, 255));
            fillrect({xtextBoxLow,bottomBoxY}, {xtextBoxHigh,fifthBoxY});
            setcolor (t_color (0, 0, 255));
            drawtext_in( t_bound_box({xtextBoxLow,bottomBoxY},{xtextBoxHigh,fifthBoxY}), suggestionsText2[4]);

            setcolor (t_color (150, 200, 255)); 
            drawline({xtextBoxLow,secondBoxY}, {xtextBoxHigh,secondBoxY});
            drawline({xtextBoxLow,thirdBoxY}, {xtextBoxHigh,thirdBoxY});
            drawline({xtextBoxLow,fourthBoxY}, {xtextBoxHigh,fourthBoxY});
            drawline({xtextBoxLow,fifthBoxY}, {xtextBoxHigh,fifthBoxY});
            drawline({xtextBoxLow,bottomBoxY}, {xtextBoxHigh,bottomBoxY});
            
            
        }else if (x>= thirdBoxY && x<= secondBoxY){
            
            //Make second box yellow and the rest white
            setcolor (t_color (255, 255, 255));
            fillrect({xtextBoxLow,secondBoxY}, {xtextBoxHigh,topBoxY});
            setcolor (t_color (0, 0, 255));
            drawtext_in( t_bound_box({xtextBoxLow,secondBoxY},{xtextBoxHigh,topBoxY}), suggestionsText2[0]);

            setcolor (t_color (255, 255, 150));
            fillrect({xtextBoxLow,thirdBoxY}, {xtextBoxHigh,secondBoxY});
            setcolor (t_color (0, 0, 255));
            drawtext_in( t_bound_box({xtextBoxLow,thirdBoxY},{xtextBoxHigh,secondBoxY}), suggestionsText2[1]);

            setcolor (t_color (255, 255, 255));
            fillrect({xtextBoxLow,fourthBoxY}, {xtextBoxHigh,thirdBoxY});
            setcolor (t_color (0, 0, 255));
            drawtext_in( t_bound_box({xtextBoxLow,fourthBoxY},{xtextBoxHigh,thirdBoxY}), suggestionsText2[2]);

            setcolor (t_color (255, 255, 255));
            fillrect({xtextBoxLow,fifthBoxY}, {xtextBoxHigh,fourthBoxY});
            setcolor (t_color (0, 0, 255));
            drawtext_in( t_bound_box({xtextBoxLow,fifthBoxY},{xtextBoxHigh,fourthBoxY}), suggestionsText2[3]);

            setcolor (t_color (255, 255, 255));
            fillrect({xtextBoxLow,bottomBoxY}, {xtextBoxHigh,fifthBoxY});
            setcolor (t_color (0, 0, 255));
            drawtext_in( t_bound_box({xtextBoxLow,bottomBoxY},{xtextBoxHigh,fifthBoxY}), suggestionsText2[4]);

            setcolor (t_color (150, 200, 255)); 
            drawline({xtextBoxLow,secondBoxY}, {xtextBoxHigh,secondBoxY});
            drawline({xtextBoxLow,thirdBoxY}, {xtextBoxHigh,thirdBoxY});
            drawline({xtextBoxLow,fourthBoxY}, {xtextBoxHigh,fourthBoxY});
            drawline({xtextBoxLow,fifthBoxY}, {xtextBoxHigh,fifthBoxY});
            drawline({xtextBoxLow,bottomBoxY}, {xtextBoxHigh,bottomBoxY});
            
        }else if (x>= fourthBoxY && x<= thirdBoxY){
           
            //Make third box yellow and the rest white
            setcolor (t_color (255, 255, 255));
            fillrect({xtextBoxLow,secondBoxY}, {xtextBoxHigh,topBoxY});
            setcolor (t_color (0, 0, 255));
            drawtext_in( t_bound_box({xtextBoxLow,secondBoxY},{xtextBoxHigh,topBoxY}), suggestionsText2[0]);

            setcolor (t_color (255, 255, 255));
            fillrect({xtextBoxLow,thirdBoxY}, {xtextBoxHigh,secondBoxY});
            setcolor (t_color (0, 0, 255));
            drawtext_in( t_bound_box({xtextBoxLow,thirdBoxY},{xtextBoxHigh,secondBoxY}), suggestionsText2[1]);

            setcolor (t_color (255, 255, 150));
            fillrect({xtextBoxLow,fourthBoxY}, {xtextBoxHigh,thirdBoxY});
            setcolor (t_color (0, 0, 255));
            drawtext_in( t_bound_box({xtextBoxLow,fourthBoxY},{xtextBoxHigh,thirdBoxY}), suggestionsText2[2]);

            setcolor (t_color (255, 255, 255));
            fillrect({xtextBoxLow,fifthBoxY}, {xtextBoxHigh,fourthBoxY});
            setcolor (t_color (0, 0, 255));
            drawtext_in( t_bound_box({xtextBoxLow,fifthBoxY},{xtextBoxHigh,fourthBoxY}), suggestionsText2[3]);

            setcolor (t_color (255, 255, 255));
            fillrect({xtextBoxLow,bottomBoxY}, {xtextBoxHigh,fifthBoxY});
            setcolor (t_color (0, 0, 255));
            drawtext_in( t_bound_box({xtextBoxLow,bottomBoxY},{xtextBoxHigh,fifthBoxY}), suggestionsText2[4]);

            setcolor (t_color (150, 200, 255)); 
            drawline({xtextBoxLow,secondBoxY}, {xtextBoxHigh,secondBoxY});
            drawline({xtextBoxLow,thirdBoxY}, {xtextBoxHigh,thirdBoxY});
            drawline({xtextBoxLow,fourthBoxY}, {xtextBoxHigh,fourthBoxY});
            drawline({xtextBoxLow,fifthBoxY}, {xtextBoxHigh,fifthBoxY});
            drawline({xtextBoxLow,bottomBoxY}, {xtextBoxHigh,bottomBoxY});
            
        }else if (x>= fifthBoxY && x<= fourthBoxY){
            
            //Make fourth box yellow and the rest white
            setcolor (t_color (255, 255, 255));
            fillrect({xtextBoxLow,secondBoxY}, {xtextBoxHigh,topBoxY});
            setcolor (t_color (0, 0, 255));
            drawtext_in( t_bound_box({xtextBoxLow,secondBoxY},{xtextBoxHigh,topBoxY}), suggestionsText2[0]);

            setcolor (t_color (255, 255, 255));
            fillrect({xtextBoxLow,thirdBoxY}, {xtextBoxHigh,secondBoxY});
            setcolor (t_color (0, 0, 255));
            drawtext_in( t_bound_box({xtextBoxLow,thirdBoxY},{xtextBoxHigh,secondBoxY}), suggestionsText2[1]);

            setcolor (t_color (255, 255, 255));
            fillrect({xtextBoxLow,fourthBoxY}, {xtextBoxHigh,thirdBoxY});
            setcolor (t_color (0, 0, 255));
            drawtext_in( t_bound_box({xtextBoxLow,fourthBoxY},{xtextBoxHigh,thirdBoxY}), suggestionsText2[2]);

            setcolor (t_color (255, 255, 150));
            fillrect({xtextBoxLow,fifthBoxY}, {xtextBoxHigh,fourthBoxY});
            setcolor (t_color (0, 0, 255));
            drawtext_in( t_bound_box({xtextBoxLow,fifthBoxY},{xtextBoxHigh,fourthBoxY}), suggestionsText2[3]);

            setcolor (t_color (255, 255, 255));
            fillrect({xtextBoxLow,bottomBoxY}, {xtextBoxHigh,fifthBoxY});
            setcolor (t_color (0, 0, 255));
            drawtext_in( t_bound_box({xtextBoxLow,bottomBoxY},{xtextBoxHigh,fifthBoxY}), suggestionsText2[4]);

            setcolor (t_color (150, 200, 255)); 
            drawline({xtextBoxLow,secondBoxY}, {xtextBoxHigh,secondBoxY});
            drawline({xtextBoxLow,thirdBoxY}, {xtextBoxHigh,thirdBoxY});
            drawline({xtextBoxLow,fourthBoxY}, {xtextBoxHigh,fourthBoxY});
            drawline({xtextBoxLow,fifthBoxY}, {xtextBoxHigh,fifthBoxY});
            drawline({xtextBoxLow,bottomBoxY}, {xtextBoxHigh,bottomBoxY});
            
        }else{
            
            //Make fifth box yellow and the rest white
            setcolor (t_color (255, 255, 255));
            fillrect({xtextBoxLow,secondBoxY}, {xtextBoxHigh,topBoxY});
            setcolor (t_color (0, 0, 255));
            drawtext_in( t_bound_box({xtextBoxLow,secondBoxY},{xtextBoxHigh,topBoxY}), suggestionsText2[0]);

            setcolor (t_color (255, 255, 255));
            fillrect({xtextBoxLow,thirdBoxY}, {xtextBoxHigh,secondBoxY});
            setcolor (t_color (0, 0, 255));
            drawtext_in( t_bound_box({xtextBoxLow,thirdBoxY},{xtextBoxHigh,secondBoxY}), suggestionsText2[1]);

            setcolor (t_color (255, 255, 255));
            fillrect({xtextBoxLow,fourthBoxY}, {xtextBoxHigh,thirdBoxY});
            setcolor (t_color (0, 0, 255));
            drawtext_in( t_bound_box({xtextBoxLow,fourthBoxY},{xtextBoxHigh,thirdBoxY}), suggestionsText2[2]);

            setcolor (t_color (255, 255, 255));
            fillrect({xtextBoxLow,fifthBoxY}, {xtextBoxHigh,fourthBoxY});
            setcolor (t_color (0, 0, 255));
            drawtext_in( t_bound_box({xtextBoxLow,fifthBoxY},{xtextBoxHigh,fourthBoxY}), suggestionsText2[3]);

            setcolor (t_color (255, 255, 150));
            fillrect({xtextBoxLow,bottomBoxY}, {xtextBoxHigh,fifthBoxY});
            setcolor (t_color (0, 0, 255));
            drawtext_in( t_bound_box({xtextBoxLow,bottomBoxY},{xtextBoxHigh,fifthBoxY}), suggestionsText2[4]);

            setcolor (t_color (150, 200, 255)); 
            drawline({xtextBoxLow,secondBoxY}, {xtextBoxHigh,secondBoxY});
            drawline({xtextBoxLow,thirdBoxY}, {xtextBoxHigh,thirdBoxY});
            drawline({xtextBoxLow,fourthBoxY}, {xtextBoxHigh,fourthBoxY});
            drawline({xtextBoxLow,fifthBoxY}, {xtextBoxHigh,fifthBoxY});
            drawline({xtextBoxLow,bottomBoxY}, {xtextBoxHigh,bottomBoxY});
            
        }
        

    }else{
        
        for (auto iter = mapDatabase->POI_beginIter(); iter != mapDatabase->POI_endIter(); iter++) {
            if (isClicked(getPOIType(iter->first)) != false) {
                float poiRadiusX = abs(iter->second.lat - x);
                float poiRadiusY = abs((iter-> second.lon) - y);

                if (poiRadiusX <= POI_RADIUS && poiRadiusY <= POI_RADIUS) {
                    drawScreen();
                    setcolor(0, 0, 255);// DEBUG HERE // Blue
                    drawtext({y, x + VERTICAL_TEXT_OFFSET}, getPointOfInterestName((iter->first)), find_street_segment_length(iter->first), find_street_segment_length(iter->first));
                }
            }
        }
    }
}

// Function to draw the red pin on mouse click
// Maintains location even on drawscreen()
void drawPinDrops(){
    t_bound_box visibleWorld = get_visible_world();
    
    float width = visibleWorld.get_width();
    float height = visibleWorld.get_height();

    // Created ratio for pin size and visible map coordinates
    float aspectRatio = (height+width)/2 * 0.04;
    
    for (auto iter = pinDropPoints.begin(); iter != pinDropPoints.end(); iter++){
        setcolor (t_color (255, 0, 0)); // Red
        fillarc(iter->lat, iter->lon, aspectRatio, 65,50);   
    } 
}


void drawSearchBar(){
    
    if (searchClicked){
        t_bound_box visibleWorld = get_visible_world();
        
        float xLeft = visibleWorld.left();          
        float yTop = visibleWorld.top();
        float width = visibleWorld.get_width();
        float height = visibleWorld.get_height();
        float heightBox = yTop - height*1/20 - (yTop - height*1/12);
        
        
        //----------------------- Background Box  ------------------------//
        
        t_point bottomLeft = {xLeft + width*1/20, yTop - height*1/11 - heightBox - heightBox};
        t_point upperRight = {xLeft + width*3/5, yTop - height*1/20 + heightBox};   
    
        setcolor (t_color (140, 140, 140));
        fillrect(bottomLeft, upperRight);
 
        //----------------------- Draw First Text Box ------------------------//
        
        bottomLeft = {xLeft + width*1/20, yTop - height*1/12};
        upperRight = {xLeft + width*3/5, yTop - height*1/20};   
    
        setcolor (t_color (255, 255, 255));
        fillrect(bottomLeft, upperRight);

        setcolor (t_color (0, 0, 0));
        drawtext_in(t_bound_box(bottomLeft,upperRight), intersectionInput1);
        
        //----------------------- Draw Second Text Box ------------------------//
        
        bottomLeft = {xLeft + width*1/20, yTop - height*1/11 - heightBox};
        upperRight = {xLeft + width*3/5, yTop - height*1/11};   
    
        setcolor (t_color (255, 255, 255));
        fillrect(bottomLeft, upperRight);
        
        setcolor (t_color (0, 0, 0));
        drawtext_in(t_bound_box(bottomLeft,upperRight), intersectionInput2);
        
        //----------------------- Text Box 1 Label ------------------------//
        
        bottomLeft = {xLeft + width*1/20, yTop - height*1/20};
        upperRight = {xLeft + width*1/5, yTop - height*1/20 + heightBox};   
        
        setcolor (t_color (0, 0, 0));
        fillrect(bottomLeft, upperRight);
  
        setcolor (t_color (255, 255, 255));
        drawtext_in(t_bound_box(bottomLeft,upperRight), "Starting Intersection");
        
        //----------------------- Text Box 2 Label ------------------------//
 
        bottomLeft = {xLeft + width*1/20, yTop - height*1/11 - 2*heightBox};
        upperRight = {xLeft + width*1/5, yTop - height*1/11 - heightBox};   
        
        setcolor (t_color (0, 0, 0));
        fillrect(bottomLeft, upperRight);
  
        setcolor (t_color (255, 255, 255));
        drawtext_in(t_bound_box(bottomLeft,upperRight), "Destination");
        
        
        //----------------------- Draw Find Path Button ------------------------//
       
        bottomLeft = {xLeft + width/2, yTop - height*1/11 - heightBox - heightBox};
        upperRight = {xLeft + width*3/5, yTop - height*1/10 - heightBox};   
        
        setcolor (t_color (150, 200, 255));
        fillrect(bottomLeft, upperRight);
  
        setcolor (t_color (0, 0, 0));
        drawtext_in(t_bound_box(bottomLeft,upperRight), "Find Path");
        
        //----------------------- Click Boxes for POI/2nd Intersection ------------------------//
        
        setcolor (t_color (255, 255, 255));
        
        // POI 
        bottomLeft = {xLeft + width*21/100, yTop - height*1/11 - heightBox - heightBox};
        upperRight = {xLeft + width*24/100, yTop - height*1/10 - heightBox};   
        fillrect(bottomLeft, upperRight); 
        
        bottomLeft = {xLeft + width*24/100, yTop - height*1/11 - heightBox - heightBox};
        upperRight = {xLeft + width*30/100, yTop - height*1/10 - heightBox};  
        drawtext_in(t_bound_box(bottomLeft,upperRight), "POI");
  
        // Intersection
        bottomLeft = {xLeft + width*32/100, yTop - height*1/11 - heightBox - heightBox};
        upperRight = {xLeft + width*35/100, yTop - height*1/10 - heightBox};   
        fillrect(bottomLeft, upperRight);
        
        bottomLeft = {xLeft + width*35/100, yTop - height*1/11 - heightBox - heightBox};
        upperRight = {xLeft + width*46/100, yTop - height*1/10 - heightBox};  
        drawtext_in(t_bound_box(bottomLeft,upperRight), "Intersection");
        
        //--------------------------- Click Box Xs ----------------------------//
        setcolor (t_color (0, 0, 0));
        if (checkBox1Clicked){
            
            drawline(xLeft + width*21/100,yTop - height*1/11 - heightBox - heightBox,xLeft + width*24/100,yTop - height*1/10 - heightBox);
            drawline(xLeft + width*21/100,yTop - height*1/10 - heightBox,xLeft + width*24/100,yTop - height*1/11 - heightBox - heightBox);
        
        }else if(checkBox2Clicked){
        
            drawline(xLeft + width*32/100,yTop - height*1/11 - heightBox - heightBox,xLeft + width*35/100,yTop - height*1/10 - heightBox);
            drawline(xLeft + width*32/100,yTop - height*1/10 - heightBox,xLeft + width*35/100,yTop - height*1/11 - heightBox - heightBox);
            
        }

    // if searchClick is false, then do nothing 
    }
}

void drawHelpScreen() {
    
    if (helpClicked) {
            
        t_bound_box visibleWorld = get_visible_world();
        float xLeft = visibleWorld.left();   
        float xRight = visibleWorld.right();
        float yTop = visibleWorld.top();
        float yBottom = visibleWorld.bottom();
        float width = visibleWorld.get_width();
        float height = visibleWorld.get_height();
        
        //----------------------- Set Background  ------------------------//
        
        setcolor(DARKGREY);
        fillrect({xLeft, yBottom}, {xRight, yTop});
        
        //----------------------- Make Title  ---------------------------//
         
        t_point bottomLeft = {xLeft + width*1/20, yTop - height*1/12};
        t_point upperRight = {xLeft + width*3/5, yTop - height*1/30};
        
        setcolor(LIGHTGREY);
        fillrect(bottomLeft, upperRight);
  
        setcolor(t_color (20, 54, 131));
        setfontsize(20);
        drawtext_in(t_bound_box(bottomLeft, upperRight), "Welcome to the Help screen!");
        
        //--------------- Make Description Box Background ---------------//
        
        bottomLeft = {xLeft + width*1/20, yBottom + height*1/12};
        upperRight = {xRight - width*1/20, yTop - height*1/8};
        
        setcolor(LIGHTGREY);
        fillrect(bottomLeft, upperRight);
        
        //--------------- Make Description Box & Text ---------------//
        
        bottomLeft = {xLeft + width*1/20, yTop - height*1/6};
        upperRight = {xLeft + width*3/20, yTop - height*1/8};
        
        setcolor(t_color (20, 54, 131));
        setfontsize(14);
        drawtext_in(t_bound_box(bottomLeft, upperRight), "Mouse");
        
        
        bottomLeft = {xLeft + width*1/45, yTop - height*1/5};
        upperRight = {xLeft + width*9/10, yTop - height*1/6};
        
        setcolor(t_color (33, 78, 183));
        setfontsize(12);
        drawtext_in(t_bound_box(bottomLeft, upperRight), "Left-click: drop pins on map / select where to type (if search box enabled)");
        
        bottomLeft = {xLeft + width*1/10, yTop - height*1/4};
        upperRight = {xLeft + width*7/10, yTop - height*1/5};
        
        drawtext_in(t_bound_box(bottomLeft, upperRight), "Mouse-wheel: click and hold to pan map; roll to toggle zoom");
        
        bottomLeft = {xLeft + width*3/40, yTop - height*5/15};
        upperRight = {xLeft + width*5/10, yTop - height*4/15};
        
        setcolor(DARKGREEN);
        
        drawtext_in(t_bound_box(bottomLeft, upperRight), "Everything else is self-explanatory...");
        
        setcolor(t_color (33, 78, 183));
        
        //--------------- Filter Buttons Help ---------------//
        
        drawline(xRight - width*1/30, yTop - height*2/9, xRight - width*1/30, yBottom + height*3/7);
        drawline(xRight - width*1/30, yTop - height*2/9, xRight - width*1/70, yTop - height*2/9);
        drawline(xRight - width*1/30, yBottom + height*3/7, xRight - width*1/70, yBottom + height*3/7);
        
        bottomLeft = {xLeft + width*10/16, yTop - height*3/5};
        upperRight = {xRight - width*1/25, yTop - height*1/5};
        
        drawtext_in(t_bound_box(bottomLeft, upperRight), "Toggle point of interests by type");
        
        //--------------- Search Button Help ---------------//
        
        drawline(xLeft + width*14/16, yTop - height*27/40, xRight - width*1/50, yTop - height*27/40);
        
        bottomLeft = {xLeft + width*10/16, yTop - height*28/40};
        upperRight = {xRight - width*3/25, yTop - height*26/40};
        
        //setcolor(RED);
        //fillrect(bottomLeft, upperRight);
        
        
        if (searchClicked) {
            drawtext_in(t_bound_box(bottomLeft, upperRight), "Close direction-finding");
        }
        
        else {
            drawtext_in(t_bound_box(bottomLeft, upperRight), "Open direction-finding");
        }
    }
}

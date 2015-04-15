#include "UserInput.h"


// Returns a vector of all intersection names
vector<string> getAllIntersectionNames() {
    vector<string> intersectionNames;
    
    for (unsigned id = 0; id < getNumberOfIntersections(); id++) {
        intersectionNames.push_back(getIntersectionName(id));
    }
    
    return intersectionNames;
}

// Allows user to select which map they would like to load
string selectMap(string mapIn){
    string map;
    
    // First letter ommitted to account for capital or lowercase
    if (mapIn.find("airo", 0) != std::string::npos) {
        map = "cairo_egypt.bin";
    }
    else if (mapIn.find("oscow", 0) != std::string::npos) {
        map = "moscow.bin";
    }
    else if (mapIn.find("aint", 0) != std::string::npos || 
            mapIn.find("st", 0) != std::string::npos ||
            mapIn.find("St", 0) != std::string::npos) {
        map = "saint_helena.bin";
    }
    else if (mapIn.find("oronto", 0) != std::string::npos) {
        map = "toronto.bin";
    }
    else if (mapIn.find("gta",0) != std::string::npos ||
            mapIn.find("GTA",0) != std::string::npos ||
            mapIn.find("reater",0) != std::string::npos ||
            mapIn.find("oronto_canada",0) != std::string::npos) {
        map = "toronto_canada.bin";
    }
    else if (mapIn.find("ew",0) != std::string::npos) {
        map = "newyork.bin";
    }
    else if (mapIn.find("amilton", 0) != std::string::npos) {
        map = "hamilton_canada.bin";
    }
    else {
        map = "invalid";
    }
    
    return map;
}

// GNU readline
char* acceptUserInput(const char* promptText) {
    // r1_bind_key('\t', r1_complete);
    // r1_attempted_completion_function = command_completion;
    // r1_completer_quote_characters = strdup("\"\'");
    
    char* buf;
    
    buf = readline(promptText);  // Prompt user for input
    
    if (strcmp(buf, "") != 0) { // Do not add blanks to input history
        add_history(buf);
    }

    // If the buffer wasn't freed in the main loop, we need to free it now
    //free (buf); 
    //buf = NULL; // Mark as NULL to show we freed it

    return buf;
}

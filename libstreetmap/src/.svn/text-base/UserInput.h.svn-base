#include <iostream>
#include <cstdlib>
#include <vector>
#include <regex>

#include "StreetsDatabaseAPI.h"
#include <readline/readline.h>
#include <readline/history.h>

using namespace std;

char** command_completion(const char* stem_text, int start, int end);
char* intersection_name_generator(const char* stem_text, int state);

// Returns a vector of all intersection names
vector<string> getAllIntersectionNames();

// Allows user to select which map they would like to load
string selectMap(string mapIn);

// GNU readline
char* acceptUserInput(const char* promptText);
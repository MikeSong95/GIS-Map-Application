#include <algorithm>
#include <random>
#include <unittest++/UnitTest++.h>
#include "unit_test_util.h"
#include "m3.h>
#include "UserInput.h"
#include "AStarFunctions.h"

extern MapDatabase* mapDatabase;

struct Map_Fixture {
	Map_Fixture() {
		//RNG Setup
		rng = std::minstd_rand(0);
		rand_intersection = std::uniform_int_distribution<unsigned>(0,getNumberOfIntersections()-1);
		rand_street = std::uniform_int_distribution<unsigned>(0,getNumberOfStreets()-1);
		rand_segment = std::uniform_int_distribution<unsigned>(0,getNumberOfStreetSegments()-1);
	}
	~Map_Fixture() {
	}
	std::minstd_rand rng;
	std::uniform_int_distribution<unsigned> rand_intersection;
	std::uniform_int_distribution<unsigned> rand_street;
	std::uniform_int_distribution<unsigned> rand_segment;
};

SUITE(M3_UnitTests) {
    /*TEST_FIXTURE(Map_Fixture, intersection_graph_functionality) {
        // Check correct adjacent intersections of an intersection
        vector <unsigned> expected; 
        vector <unsigned> actual;
 
        for (unsigned j = 0; j < getNumberOfIntersections(); j++) {
            for (unsigned i = 0; i < mapDatabase->getStreetEdges(j).size(); i++) {
                actual.push_back(mapDatabase->getStreetEdges(j)[i].getTargetIntersection());
            }
            
            sort (actual.begin(), actual.end());
            actual.erase(unique(actual.begin(), actual.end()), actual.end());
            
            expected = find_adjacent_intersections(getIntersectionName(j));
            sort (expected.begin(), expected.end());
            
            CHECK_EQUAL(expected, actual);
            
            actual.clear();
            expected.clear();
        }  
*/

    TEST_FIXTURE(Map_Fixture, getMaxSpeedLimitTests) {
        
        double expected, actual;
        
        expected = 100;
        actual = getMaxSpeedLimit();
        
        CHECK_EQUAL(expected, actual);
    }
    
    TEST_FIXTURE(Map_Fixture, addTurnTimeMin_functionTests) {
            
        double expected, actual;
        
        // yes turn; different street name
        expected = 15 / 60;
        
        actual = addTurnTimeMin(2143, 2144); 
        CHECK_EQUAL(expected, actual);
        
        actual = addTurnTimeMin(3358, 3359); 
        CHECK_EQUAL(expected, actual);
        
        actual = addTurnTimeMin(9758, 9759); 
        CHECK_EQUAL(expected, actual);
        
        actual = addTurnTimeMin(12073, 12074); 
        CHECK_EQUAL(expected, actual);
        
        actual = addTurnTimeMin(14108, 14109); 
        CHECK_EQUAL(expected, actual);
        
        actual = addTurnTimeMin(14107, 14108); 
        CHECK_EQUAL(expected, actual);
        
        actual = addTurnTimeMin(14410, 14411); 
        CHECK_EQUAL(expected, actual);
        
        actual = addTurnTimeMin(15855, 15856); 
        CHECK_EQUAL(expected, actual);
        
        actual = addTurnTimeMin(17153, 17154); 
        CHECK_EQUAL(expected, actual);
        
        actual = addTurnTimeMin(18130, 18131);
        CHECK_EQUAL(expected, actual);
        
        // no turn; same street name
        expected = 0;
        
        actual = addTurnTimeMin(1773, 1774);
        CHECK_EQUAL(expected, actual);
                
        actual = addTurnTimeMin(1810, 1811);
        CHECK_EQUAL(expected, actual);
        
        actual = addTurnTimeMin(2307, 2308);        
        CHECK_EQUAL(expected, actual);
        
        actual = addTurnTimeMin(2601, 2602);
        CHECK_EQUAL(expected, actual);
        
        actual = addTurnTimeMin(2726, 2727);
        CHECK_EQUAL(expected, actual);
        
        actual = addTurnTimeMin(13252, 13253);
        CHECK_EQUAL(expected, actual);
        
        actual = addTurnTimeMin(14226, 14227);
        CHECK_EQUAL(expected, actual);
        
        actual = addTurnTimeMin(16607, 16608);
        CHECK_EQUAL(expected, actual);
        
        actual = addTurnTimeMin(18135, 18136);
        CHECK_EQUAL(expected, actual);
        
        actual = addTurnTimeMin(18250, 18251);
        CHECK_EQUAL(expected, actual);
    }
    
    
    // Test all intersection names are correct
    TEST_FIXTURE(Map_Fixture, user_input_get_all_intersection_names) {
        // Check correct adjacent intersections of an intersection
        string expected; 
        vector <string> actual;
        
        actual = getAllIntersectionNames();
        
        for (unsigned id = 0; id < getNumberOfIntersections(); id++) {
            expected = getIntersectionName(id);
            CHECK_EQUAL(expected, actual[id]);
        }  
    }
    
    TEST_FIXTURE(Map_Fixture, heuristicTests) {        
        
        double expected, actual;

        // divide expected by 100 because that is the max speed limit of toronto.bin
        expected = 60 * 0 / 100;
	actual = heuristic(1648, 1648);
	CHECK(relative_error(expected, actual) < 0.03);
		
	expected = 60 * 5795.502445682106 / 100;
	actual = heuristic(1648, 23162);
	CHECK(relative_error(expected, actual) < 0.03);
		
	expected = 60 * 1004.891712468667 / 100;
	actual = heuristic(58114, 2298);
	CHECK(relative_error(expected, actual) < 0.03);
		
	expected = 60 * 1043.156730450085 / 100;
	actual = heuristic(3023, 2522);
	CHECK(relative_error(expected, actual) < 0.03);
		
	expected = 60 * 245.2059793921245 / 100;
	actual = heuristic(40201, 10538);
	CHECK(relative_error(expected, actual) < 0.03);
		
	expected = 60 * 223.8238412168463 / 100;
	actual = heuristic(1896, 27814);
	CHECK(relative_error(expected, actual) < 0.03);
		
	expected = 60 * 4857.506545485718 / 100;
	actual = heuristic(659, 9555);
	CHECK(relative_error(expected, actual) < 0.03);
		
	expected = 60 * 1006.653578635471 / 100;
	actual = heuristic(2972, 3482);
	CHECK(relative_error(expected, actual) < 0.03);
		
	expected = 60 * 2501.190986258448 / 100;
	actual = heuristic(1851, 58107);
	CHECK(relative_error(expected, actual) < 0.03);
		
	expected = 60 * 1304.44114716316 / 100;
	actual = heuristic(5438, 1376);
	CHECK(relative_error(expected, actual) < 0.03);
		
	expected = 60 * 1287.545927657807 / 100;
	actual = heuristic(5720, 5600);
	CHECK(relative_error(expected, actual) < 0.03);
		
	expected = 60 * 1469.49560721438 / 100;
	actual = heuristic(3369, 63371);
	CHECK(relative_error(expected, actual) < 0.03);
		
	expected = 60 * 2784.653422257717 / 100;
	actual = heuristic(130357, 5450);
	CHECK(relative_error(expected, actual) < 0.03);
    }
}

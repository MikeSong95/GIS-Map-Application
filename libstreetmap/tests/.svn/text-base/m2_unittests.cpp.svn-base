#include <random>
#include <string>
#include <unittest++/UnitTest++.h>
#include "unit_test_util.h"
#include "StreetsDatabaseAPI.h"
#include "MapDatabase.h"

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

SUITE(Features_Tests) {
    
    TEST_FIXTURE(Map_Fixture, naturalFeatureTests) {
        string expected, actual;
        
        expected = getFeatureAttribute(32,"natural"); // given function in StreetsDatabaseAPI.h
        actual = mapDatabase->getFeatureValue(32); // self-implemented function in MapDatabase.h that utilizes self-created data structure
        CHECK_EQUAL(expected,actual);
        
        expected = getFeatureAttribute(54,"natural");
        actual = mapDatabase->getFeatureValue(54);
        CHECK_EQUAL(expected,actual);
        
        expected = getFeatureAttribute(550,"natural");
        actual = mapDatabase->getFeatureValue(550);
        CHECK_EQUAL(expected,actual);
        
        expected = getFeatureAttribute(909,"natural");
        actual = mapDatabase->getFeatureValue(909);
        CHECK_EQUAL(expected,actual);
        
        expected = getFeatureAttribute(1493,"natural");
        actual = mapDatabase->getFeatureValue(1493);
        CHECK_EQUAL(expected,actual);
        
        expected = getFeatureAttribute(1684,"natural");
        actual = mapDatabase->getFeatureValue(1684);
        CHECK_EQUAL(expected,actual);
        
        expected = getFeatureAttribute(4555,"natural");
        actual = mapDatabase->getFeatureValue(4555);
        CHECK_EQUAL(expected,actual);
        
        expected = getFeatureAttribute(6739,"natural");
        actual = mapDatabase->getFeatureValue(6739);
        CHECK_EQUAL(expected,actual);
        
        expected = getFeatureAttribute(9077,"natural");
        actual = mapDatabase->getFeatureValue(9077);
        CHECK_EQUAL(expected,actual);
        
        expected = getFeatureAttribute(9999,"natural");
        actual = mapDatabase->getFeatureValue(9999);
        CHECK_EQUAL(expected,actual);
        
        expected = getFeatureAttribute(10912,"natural");
        actual = mapDatabase->getFeatureValue(10912);
        CHECK_EQUAL(expected,actual);
        
        expected = getFeatureAttribute(12646,"natural");
        actual = mapDatabase->getFeatureValue(12646);
        CHECK_EQUAL(expected,actual);
        
        expected = getFeatureAttribute(13236,"natural");
        actual = mapDatabase->getFeatureValue(13236);
        CHECK_EQUAL(expected,actual);
        
    }
    
    TEST_FIXTURE(Map_Fixture, waterFeatureTests) {
        // All expected output should be water
        string expected = "water", actual;
        
        actual = mapDatabase->getFeatureValue(11606);
        CHECK_EQUAL(expected,actual);
        
        actual = mapDatabase->getFeatureValue(11662);
        CHECK_EQUAL(expected,actual);
        
        actual = mapDatabase->getFeatureValue(12765);
        CHECK_EQUAL(expected,actual);
        
        actual = mapDatabase->getFeatureValue(12787);
        CHECK_EQUAL(expected,actual);
        
        actual = mapDatabase->getFeatureValue(12887);
        CHECK_EQUAL(expected,actual);
        
        actual = mapDatabase->getFeatureValue(12906);
        CHECK_EQUAL(expected,actual);
        
        actual = mapDatabase->getFeatureValue(12922);
        CHECK_EQUAL(expected,actual);
        
        actual = mapDatabase->getFeatureValue(13083);
        CHECK_EQUAL(expected,actual);
        
        actual = mapDatabase->getFeatureValue(13087);
        CHECK_EQUAL(expected,actual);
        
        actual = mapDatabase->getFeatureValue(13088);
        CHECK_EQUAL(expected,actual);
        
        actual = mapDatabase->getFeatureValue(13089);
        CHECK_EQUAL(expected,actual);
        
        actual = mapDatabase->getFeatureValue(13101);
        CHECK_EQUAL(expected,actual);
        
    }
     
    
    TEST_FIXTURE(Map_Fixture, landFeatureTests) {
        string expected, actual;
        unsigned numFeaturesTest = 100;
        
        // this algorithm automates the testing process and makes it comprehensive, i.e. tests all ID values
        for (unsigned i = 0; i < numFeaturesTest; i++) {
            expected = getFeatureAttribute(i,"land");
            actual = mapDatabase->getFeatureValue(i);
            
            // if we are inspecting a LEISURE feature according to given function
            if (expected != "") {
                CHECK_EQUAL(expected,actual);
            }
            // if we aren't inspecting a LEISURE feature according to given function, return empty string
            else {
                CHECK(expected != actual);
            }
        }
        
        expected = getFeatureAttribute(13238,"land");
        actual = mapDatabase->getFeatureValue(13238);
        CHECK_EQUAL(expected,actual);
        
        expected = getFeatureAttribute(13239,"land");
        actual = mapDatabase->getFeatureValue(13239);
        CHECK_EQUAL(expected,actual);
        
        expected = getFeatureAttribute(13243,"land");
        actual = mapDatabase->getFeatureValue(13243);
        CHECK_EQUAL(expected,actual);
        
        expected = getFeatureAttribute(13248,"land");
        actual = mapDatabase->getFeatureValue(13248);
        CHECK_EQUAL(expected,actual);
        
        expected = getFeatureAttribute(13250,"land");
        actual = mapDatabase->getFeatureValue(13250);
        CHECK_EQUAL(expected,actual);
        
        expected = getFeatureAttribute(13251,"land");
        actual = mapDatabase->getFeatureValue(13251);
        CHECK_EQUAL(expected,actual);
        
        expected = getFeatureAttribute(13252,"land");
        actual = mapDatabase->getFeatureValue(13252);
        CHECK_EQUAL(expected,actual);
        
        expected = getFeatureAttribute(13253,"land");
        actual = mapDatabase->getFeatureValue(13253);
        CHECK_EQUAL(expected,actual);
        
        expected = getFeatureAttribute(13258,"land");
        actual = mapDatabase->getFeatureValue(13258);
        CHECK_EQUAL(expected,actual);
        
        expected = getFeatureAttribute(13261,"land");
        actual = mapDatabase->getFeatureValue(13261);
        CHECK_EQUAL(expected,actual);
        
        expected = getFeatureAttribute(13263,"land");
        actual = mapDatabase->getFeatureValue(13263);
        CHECK_EQUAL(expected,actual);
        
        expected = getFeatureAttribute(13269,"land");
        actual = mapDatabase->getFeatureValue(13269);
        CHECK_EQUAL(expected,actual);
        
        expected = getFeatureAttribute(13270,"land");
        actual = mapDatabase->getFeatureValue(13270);
        CHECK_EQUAL(expected,actual);
    }
    

    TEST_FIXTURE(Map_Fixture, leisureFeatureTests) {
        string expected, actual;
        unsigned numFeaturesTest = 100;
        
        for (unsigned i = 0; i < numFeaturesTest; i++) {
            expected = getFeatureAttribute(i,"leisure");
            actual = mapDatabase->getFeatureValue(i);
            
            // if we are inspecting a LEISURE feature according to given function
            if (expected != "") {
                CHECK_EQUAL(expected,actual);
            }
            // if we aren't inspecting a LEISURE feature according to given function, return empty string
            else {
                CHECK(expected != actual);
            }
        }
        
        // included this for last time, as "transition" into the above algorithm testing method
        expected = getFeatureAttribute(0,"leisure");
        actual = mapDatabase->getFeatureValue(0);
        CHECK_EQUAL(expected,actual);
        
        expected = getFeatureAttribute(6,"leisure");
        actual = mapDatabase->getFeatureValue(6);
        CHECK_EQUAL(expected,actual);
        
        expected = getFeatureAttribute(85,"leisure");
        actual = mapDatabase->getFeatureValue(85);
        CHECK_EQUAL(expected,actual);
        
        expected = getFeatureAttribute(184,"leisure");
        actual = mapDatabase->getFeatureValue(184);
        CHECK_EQUAL(expected,actual);
        
        expected = getFeatureAttribute(1212,"leisure");
        actual = mapDatabase->getFeatureValue(1212);
        CHECK_EQUAL(expected,actual);
        
        expected = getFeatureAttribute(1620,"leisure");
        actual = mapDatabase->getFeatureValue(1620);
        CHECK_EQUAL(expected,actual);
        
        expected = getFeatureAttribute(2051,"leisure");
        actual = mapDatabase->getFeatureValue(2051);
        CHECK_EQUAL(expected,actual);
        
        expected = getFeatureAttribute(2077,"leisure");
        actual = mapDatabase->getFeatureValue(2077);
        CHECK_EQUAL(expected,actual);
        
        expected = getFeatureAttribute(8619,"leisure");
        actual = mapDatabase->getFeatureValue(8619);
        CHECK_EQUAL(expected,actual);
        
        expected = getFeatureAttribute(10802,"leisure");
        actual = mapDatabase->getFeatureValue(10802);
        CHECK_EQUAL(expected,actual);
        
        expected = getFeatureAttribute(11962,"leisure");
        actual = mapDatabase->getFeatureValue(11962);
        CHECK_EQUAL(expected,actual);
        
        expected = getFeatureAttribute(13234,"leisure");
        actual = mapDatabase->getFeatureValue(13234);
        CHECK_EQUAL(expected,actual);
    }
    
    TEST_FIXTURE(Map_Fixture, landuseFeatureTests) {
        string expected, actual;
        unsigned numFeaturesTest = 100;
        
        for (unsigned i = 0; i < numFeaturesTest; i++) {
            expected = getFeatureAttribute(i,"landuse");
            actual = mapDatabase->getFeatureValue(i);
            
            // if we are inspecting a LANDUSE feature according to given function
            if (expected != "") {
                CHECK_EQUAL(expected,actual);
            }
             //if we aren't inspecting a LANDUSE feature according to given function, return empty string
            else {
                CHECK(expected != actual);
            }
        }
    }
    
    TEST_FIXTURE(Map_Fixture, featurePointsTests) {
        LatLon expected, actual;
        unsigned numFeaturesTest = 5;
        double setPrecision = 0.0000001;
        
        // iterate through all features
        for (unsigned i = 0; i < numFeaturesTest; i++) {
            
            // for each feature, get number of defining points
            for (unsigned j = 0; j < getFeaturePointCount(i); j++) {
                
                // using given function in StreetsDatabaseAPI.h
                expected.lon = getFeaturePoint(i,j).lon;
                expected.lat = getFeaturePoint(i,j).lat;
                
                // using self-implemented function in MapDatabase.h
                actual.lon = mapDatabase->getFeaturePoints(i)[j].x;
                actual.lat = mapDatabase->getFeaturePoints(i)[j].y;
                
              
                CHECK(relative_error(expected.lon, actual.lon) < setPrecision);
                CHECK(relative_error(expected.lat, actual.lat) < setPrecision);
            }
        }
    }
}
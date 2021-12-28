#include <gtest/gtest.h>
#include "Person.cpp"
#include "buildingexitcrossroad.cpp"
#include "Vehicle.cpp"
#include "CityObject.cpp"
#include "crossroadclass.cpp"
#include "roadlineclass.cpp"
#include "roadobjectclass.cpp"
#include "Building.cpp"
#include "Navigator.cpp"
#include "unregulatedcrossroad.cpp"
#include "iostream"

TEST(roadline_test, Constructor){
    
    UnregulatedCrossroad firstCross{ 0, 0 };
    UnregulatedCrossroad secondCross{ 0, 40 };
    RoadLineClass SornaistenRantatie{ &firstCross, &secondCross };
    std::cout << SornaistenRantatie.GetSize() <<std::endl;
    EXPECT_TRUE(SornaistenRantatie.GetSize()* 5 == 40); 

    UnregulatedCrossroad thirdCross{ 0, 80 };

    RoadLineClass Teolisuuskatu{ &firstCross, &thirdCross };

    EXPECT_TRUE(Teolisuuskatu.GetSize()* 5 == 80); 
}



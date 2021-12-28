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

TEST(crossroad_test, Constructor){
    
    UnregulatedCrossroad crossroad1{ 0, 0 };

    EXPECT_TRUE(crossroad1.getX() == 0 && crossroad1.getY() == 0); 
}


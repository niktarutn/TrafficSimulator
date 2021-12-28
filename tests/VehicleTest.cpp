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

TEST(vehicle_test, Constructor){
    Vehicle v = Vehicle(1);

    EXPECT_TRUE(v.GetSize() == 1); 
}

TEST(vehicle_test, Route){
    Vehicle v = Vehicle(1);

    UnregulatedCrossroad firstCross{ 0, 0 };
    UnregulatedCrossroad secondCross{ 20, 0 };
    UnregulatedCrossroad thirdCross{ 40, 40 };

    RoadLineClass Mannerheimintie{ &firstCross, &secondCross };
    RoadLineClass Runeberginkatu{ &secondCross, &thirdCross };

    std::vector<RoadLineClass*> route = { &Mannerheimintie, &Runeberginkatu};
    v.setRoute(route);

    EXPECT_TRUE(v.getRoute() == route); 

}



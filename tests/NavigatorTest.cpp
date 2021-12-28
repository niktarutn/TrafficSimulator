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

UnregulatedCrossroad firstCross{ 0, 0 };
UnregulatedCrossroad secondCross{ 20, 0 };
UnregulatedCrossroad thirdCross{ 40, 40 };
UnregulatedCrossroad fourthCross{ 60, 40 };
UnregulatedCrossroad fifthCross{ 60, 60 };
UnregulatedCrossroad sixthCross{ 80, 80 };

RoadLineClass Mannerheimintie{ &firstCross, &secondCross };
RoadLineClass Runeberginkatu{ &secondCross, &thirdCross };
RoadLineClass Helsiginkatu{ &thirdCross, &fourthCross };
RoadLineClass Sturenkatu{ &fourthCross, &fifthCross };
RoadLineClass Haamentie{ &thirdCross, &sixthCross };

std::vector<RoadLineClass*> map = { &Mannerheimintie, &Runeberginkatu, &Helsiginkatu, &Sturenkatu, &Haamentie };
std::vector<CrossroadClass*> crossroads = {&firstCross, &secondCross, &thirdCross, &fourthCross, &fifthCross, &sixthCross };


TEST(navigator_test, Constructor){
    Navigator n =   Navigator(map, crossroads);
    std::vector<RoadLineClass*> route = n.MakeRoute(&firstCross, &fifthCross);
    std::vector<RoadLineClass*> expected_result = {&Mannerheimintie, &Runeberginkatu, &Helsiginkatu, &Sturenkatu };
    EXPECT_EQ(route, expected_result); 
}


TEST(navigator_test, makeRoute){
    Navigator n = Navigator(map, crossroads);
    std::vector<RoadLineClass*> route = n.MakeRoute(&firstCross, &sixthCross);
    std::vector<RoadLineClass*> expected_result = {&Mannerheimintie, &Runeberginkatu, &Haamentie };

    EXPECT_EQ(route, expected_result); 
}
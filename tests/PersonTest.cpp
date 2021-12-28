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

std::vector<RoadLineClass*> roads;
std::vector<CrossroadClass*> crossroads;

Navigator* n = new Navigator(roads, crossroads);

TEST(person_test, Constructor){
    Person guy1(n);
    Person guy2(n);
    Person guy3(n);
    EXPECT_EQ(guy1.get_id(), 1);
    EXPECT_EQ(guy2.get_id(), 2);
    EXPECT_EQ(guy3.get_id(), 3);
}


TEST(person_test, Money) {
Person guy(n);
    EXPECT_EQ(guy.get_money(), 0);
    guy.remove_money(500);
    EXPECT_EQ(guy.get_money(), -500);
    guy.add_money(10000);
    EXPECT_EQ(guy.get_money(), 9500);
    EXPECT_EQ(guy.has_money(), true);
}

TEST(person_test, RandomGenerator){
    Person guy(n);
    EXPECT_NE(guy.get_time_coming(), 0);
    EXPECT_NE(guy.get_time_leaving(), 0);
}

TEST(person_test, happines){
    Person guy(n);
    EXPECT_EQ(guy.get_happiness(), 10000);
    guy.increase_happiness(1000);
    EXPECT_EQ(guy.get_happiness(), 11000);
    guy.decrease_happiness(3000);
    EXPECT_EQ(guy.get_happiness(), 8000);
    EXPECT_EQ(guy.is_happy(), true);
}
TEST(person_test, foodAndHunger){
    Person guy(n);
    EXPECT_EQ(guy.get_hunger(), 15000);
    EXPECT_EQ(guy.get_food(), 10000);
    guy.add_food(300);
    EXPECT_EQ(guy.get_food(), 10300);
    guy.eat_food(400);
    EXPECT_EQ(guy.get_food(), 10300);
    EXPECT_EQ(guy.is_hungry(), 0);
}

TEST(person_test, buildingsPersons){
    Person guy(n);
    RecreationalBuilding* building1 = new RecreationalBuilding(nullptr, 1);
    guy.set_current_place(building1);
    EXPECT_NE(guy.get_current_place(), building1);
}
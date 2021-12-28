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

UnregulatedCrossroad exitCrossroad{ 0, 0 };

TEST(building_test, Constructor){
    
    ResidentialBuilding home = ResidentialBuilding(&exitCrossroad, 1);

    EXPECT_TRUE(home.GetType() == "Residential"); 
}

TEST(building_test, vehicle_intake){
    
    ResidentialBuilding home = ResidentialBuilding(&exitCrossroad, 2);

    Vehicle v = Vehicle(1);
    bool vehicleTaken = home.takeVehicle(&v, nullptr);
    EXPECT_TRUE(vehicleTaken); 
    bool vehicleTaken2 = home.takeVehicle(&v, nullptr);
    EXPECT_TRUE(vehicleTaken2);
    bool vehicleTaken3 = home.takeVehicle(&v, nullptr);
    EXPECT_FALSE(vehicleTaken3);
    EXPECT_TRUE(home.GetVehicles().size() == 2);
}

TEST(building_test, people_intake){
    
    ResidentialBuilding home = ResidentialBuilding(&exitCrossroad, 2);

    Person guy1(nullptr);
    home.TakePerson(&guy1);
    home.TakePerson(&guy1);
    home.TakePerson(&guy1);
    std::vector<Person*> people = home.GetPeople();
    EXPECT_TRUE(people.size() == 3);

}



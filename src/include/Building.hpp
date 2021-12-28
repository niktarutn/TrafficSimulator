#ifndef BUILDING_HPP
#define BUILDING_HPP

/*-----------------------------------------------------------------------------
 * Alexey's changes for merge request
 * the class now inherits RoadObjectClass
 * added required override functions to satisfy RoadObject interfaces
 * modified the constructor for correct interraction with crossroads
 * changed the type of crossroad inside the container
 * modified Remove function to send a vehicle to the road
 *
 * CrossroadClass and RoadLineClass do not know about buildings to avoid
 * cross-dependency. They can treat buildings as RoadObjecClass* via virtual
 * functions
 *-----------------------------------------------------------------------------*/

#include "buildingexitcrossroad.hpp" //already includes vehicle and road object
#include "Person.hpp"

#include <string>
#include <vector>
/*-----------------------------------------------------------------------------
 *Abstract class Building (cannot be initialized). Works as a base class for
    RecreationalBuilding
    ResidentialBuilding
    IndustrialBuilding
    CommercialBuilding
    
All other members are common to all Buildings except for:
    performTimeStep
    (the string variable "type_")
 *-----------------------------------------------------------------------------*/
class Person;

/*-----------------------------------------------------------------------------
 *Abstract class Building (cannot be initialized). Works as a base class for
    RecreationalBuilding
    ResidentialBuilding
    IndustrialBuilding
    CommercialBuilding
    
All other members are common to all Buildings except for:
    performTimeStep
    (the string variable "type_")
 *-----------------------------------------------------------------------------*/
class Building : public RoadObjectClass
{

protected:
   
   /*To keep tracks of used IDs*/
   static unsigned int nextID;
    /*All vehicles currently in this building*/
    std::vector<Vehicle*> vehicles_;
    /*All people currently in this building*/
    std::vector<Person*> people_;
public:
    
    /*Constructor*/
    Building( CrossroadClass* exitCrossRoad, unsigned int vehiclecapacity, const std::string& type);

	/*-----------------------------------------------------------------------------
	 * Copy constructors to be forbidden 
	 *-----------------------------------------------------------------------------*/
	Building( const Building& a ) = delete;

	virtual ~Building() = default; //destructor

    /*Take in a vehicle*/
    bool takeVehicle( Vehicle* ptrToCar, const RoadObjectClass* ptrToRoadObject ) override;

    //Perform actions during a time step, implemented for each subclass separately
    virtual void performTimeStep() override = 0;

    /*Remove a vehicle*/
    bool TakeVehicleAndLeave (Person* person);

    // /*Take in a person*/
    void TakePerson(Person* person);

    /*Get the unique ID of the building*/
    unsigned int GetID() const;

    unsigned int GetVehicleCapacity() const;

    /*Get the type of the building*/
    const std::string& GetType() const;

    /*Get the CrossRoads through which the building is accessed*/
    CrossroadClass* GetExit() const;

    /*Get all vehicles currently in this building*/
    std::vector<Vehicle*> GetVehicles() const;

    /*Get all people currently in this building*/
    std::vector<Person*> GetPeople() const;

	Building& operator = ( const Building& a ) = delete;

private:

    /*The unique id of the buildin*/
    unsigned int id_;
    /*The type of the building*/
    std::string type_;
    /*The CrossRoads through which the building is accessed*/
    CrossroadClass* exitCrossRoad_;
    /*The maximum number of vehicles that fit inside the building*/
    unsigned int vehiclecapacity_;
};

class RecreationalBuilding : public Building
{
public:
    RecreationalBuilding(CrossroadClass* exitCrossRoad, unsigned int vehiclecapacity) : Building(exitCrossRoad, vehiclecapacity, "Recreational") {}

	/*-----------------------------------------------------------------------------
	 * Copy constructors to be forbidden 
	 *-----------------------------------------------------------------------------*/
	RecreationalBuilding( const RecreationalBuilding& a ) = delete;

	~RecreationalBuilding() override = default; //destructor

	RecreationalBuilding& operator = ( const RecreationalBuilding& a ) = delete;

    virtual void performTimeStep() override;
};

class ResidentialBuilding : public Building
{
public:

	/*-----------------------------------------------------------------------------
	 * Copy constructors to be forbidden 
	 *-----------------------------------------------------------------------------*/
	ResidentialBuilding( const ResidentialBuilding& a ) = delete;

	~ResidentialBuilding() override = default; //destructor

	ResidentialBuilding& operator = ( const ResidentialBuilding& a ) = delete;

    ResidentialBuilding(CrossroadClass* exitCrossRoad, unsigned int vehiclecapacity) : Building(exitCrossRoad, vehiclecapacity, "Residential") {}
    virtual void performTimeStep() override;
};

class IndustrialBuilding : public Building
{
public:
    IndustrialBuilding(CrossroadClass* exitCrossRoad, unsigned int vehiclecapacity) : Building(exitCrossRoad, vehiclecapacity, "Industrial") {}

	/*-----------------------------------------------------------------------------
	 * Copy constructors to be forbidden 
	 *-----------------------------------------------------------------------------*/
	IndustrialBuilding( const IndustrialBuilding& a ) = delete;

	~IndustrialBuilding() override = default; //destructor

	IndustrialBuilding& operator = ( const IndustrialBuilding& a ) = delete;

    virtual void performTimeStep() override;
};

class CommercialBuilding : public Building
{
public:
    CommercialBuilding(CrossroadClass* exitCrossRoad, unsigned int vehiclecapacity) : Building(exitCrossRoad, vehiclecapacity, "Commercial") {}

	/*-----------------------------------------------------------------------------
	 * Copy constructors to be forbidden 
	 *-----------------------------------------------------------------------------*/
	CommercialBuilding( const CommercialBuilding& a ) = delete;

	~CommercialBuilding() override = default; //destructor

	CommercialBuilding& operator = ( const CommercialBuilding& a ) = delete;

    virtual void performTimeStep() override;
};


#endif

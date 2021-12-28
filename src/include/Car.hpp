#ifndef CAR_HPP
#define CAR_HPP

#include "Vehicle.hpp"


/* 
* Car class, inherited from Vehicle and Navigator classes.
* Methods: 
* - GetSize()
* - MakeRoute(CrossroadClass start, CrossroadClass end)
*/

class Car: public Vehicle{
public:
    Car(int size);//: Vehicle(size), Navigator(map);
};

#endif
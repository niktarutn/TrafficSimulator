#ifndef PERSON_HPP
#define PERSON_HPP
/*
 * =====================================================================================
 *        Class:  Person
 *  Description:  Base class for persons inhabiting a city. Might become abstract when scaling
 * Contact info - Nikolai.
 * =====================================================================================
 */
#include <string>

#include <./include/Navigator.hpp>
class Vehicle;
class Building;

class Person{
private:

    Building* home_;
    Building* fav_recreational_;
    Building* fav_commercial_;
    Building* work_;
    Building* current_place_;
    Building* destination_;
    Navigator* navigator_;

    //Vehicle* current_car_;

    static unsigned int nextID_;
    unsigned int id_;
    int happiness_;
    bool occupied_;
    double money_;
    bool drivingLicense_;//will not be needed for the first iteration; will be used when pedestrians
    int hunger_;
    int food_;
    Vehicle* own_vehicle_;
    int time_leaving_;
    int time_coming_;

public:

    Person(Navigator* n, Building* home = nullptr, Building* fav_recreational = nullptr,Building* fav_commercial = nullptr, Building* work = nullptr);

    unsigned int get_id() const;

    double get_money() const;

    int get_time_leaving() const;

    int get_time_coming() const;

    int get_happiness() const;

    int get_food() const;

    int get_hunger() const;

    Building* get_destination() const;

    void reset_destination();

    Navigator* getNavigator();

    bool is_hungry() const;

    bool is_happy() const;

    bool has_money() const;

    void eat_food(int);

    void add_food(int);

    void add_money(int);

    void remove_money(int);

    void increase_happiness(int);

    void increase_hunger(int);

    void decrease_happiness(int);

    void set_destination(unsigned int);

    void set_current_place(Building*); //USE WHEN PLACING INSIDE A BUILDING

    Building* get_current_place() const;

    void performTimeStep(unsigned int);
};
#endif
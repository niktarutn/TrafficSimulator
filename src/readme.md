# Source content
This folder should contain only hpp/cpp files of your implementation. 
You can also place hpp files in a separate directory `include `.

You can create a summary of files here. It might be useful to describe 
file relations, and brief summary of their content.

1. Interfaces and Base Classes:
- CityObject class. Contains a set of properties/required functions for every object in a city (person, road, building...)
- Person class. Is a base class for persons that inhabit a city. Their behaviour is defined by factors like hunger, happiness and money. Additionally, Person object has times when it should leave home or work. Persons manage their movement in and from buildings and place themselves in Vehicles.

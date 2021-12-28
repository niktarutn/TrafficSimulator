#ifndef CITYCLASS_HPP
#define CITYCLASS_HPP

/*-----------------------------------------------------------------------------
 *  A class that represents a city with roads, crossroads, buildings, etc.
 *  Contact info - Alexey
 *-----------------------------------------------------------------------------*/

//global include
#include <fstream>
#include <iostream>
#include <sstream>
//local inlude
#include "./include/buildingexitcrossroad.hpp"
#include "./include/unregulatedcrossroad.hpp"
#include "./include/trafficlightcrossroad.hpp"
#include "./include/Vehicle.hpp"
#include "./include/roadlineclass.hpp"
#include "./include/Car.hpp"
#include "./include/Navigator.hpp"
#include "./include/Building.hpp"

class CityClass
{
    public:
        CityClass(std::string fileName);
	~CityClass();
        std::map<std::string, CrossroadClass*>& GetCrossroads();
        std::vector<std::pair<std::string,RoadLineClass*>>& GetRoads();
        std::vector<std::pair<std::string,Building*>>& GetRECBuildings();
        std::vector<std::pair<std::string,Building*>>& GetRESBuildings();
        std::vector<std::pair<std::string,Building*>>& GetINDBuildings();
        std::vector<std::pair<std::string,Building*>>& GetCOMBuildings();


    protected:

    private:
	std::string m_fileName;
	std::map<std::string, CrossroadClass*> m_crossroads;
	std::vector<std::string> m_buildingExitCrossroadsNames;
	std::vector<std::pair<std::string, RoadLineClass*>> m_roads;
	std::vector<std::pair<std::string,Building*>> m_RECbuildings;
	std::vector<std::pair<std::string,Building*>> m_RESbuildings;
	std::vector<std::pair<std::string,Building*>> m_INDbuildings;
	std::vector<std::pair<std::string,Building*>> m_COMbuildings;
};

#endif // CITYCLASS_

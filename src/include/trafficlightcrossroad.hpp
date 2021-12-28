#ifndef TRAFFICLIGHTCROSSROAD_HPP
#define TRAFFICLIGHTCROSSROAD_HPP

#include "crossroadclass.hpp"

struct TrafficLight{
	bool color{ false };
};

/*-----------------------------------------------------------------------------
 * A crossroad that allows the cars to go only when the light is green 
 * Contact info - Alexey
 *-----------------------------------------------------------------------------*/
class TrafficLightCrossroad : public CrossroadClass
{
    public:
        TrafficLightCrossroad( int x, int y, double trafficLightTimeInSeconds = defaultTrafficLightTime );

	/*-----------------------------------------------------------------------------
	 * Copy constructors to be forbidden 
	 *-----------------------------------------------------------------------------*/
	TrafficLightCrossroad( const TrafficLightCrossroad& a ) = delete;

	~TrafficLightCrossroad() override = default; //destructor

	//traffic light crossroad needs to count the time, so it overrides the
	//superclass performTimeStep()
	void performTimeStep() override;
	void addEntryAngle ( const RoadObjectClass* ptrToEntryRoad, double angle ) override;

	//the default traffic light time in seconds
	static const double defaultTrafficLightTime;

	TrafficLightCrossroad& operator = ( const TrafficLightCrossroad& a ) = delete;

    protected:

    private:

	bool checkRightToGo
		( const RoadObjectClass* ptrToEntry, RoadObjectClass* ptrToExit ) override;

	//the time to switch the green light in perfomTimeStep()'s
	const std::size_t m_trafficLightTime;

	//the number of seconds for every performTimeStep()
	static const double tickTime;
	//allowed difference from 180Degress angle for two roads to have
	//the same traffic light, in radians
	static const double angleDifference;

	//the current time passed from the light switch in performTimeStep()'s
	
	std::size_t m_lightCounter;

	//every traffic light is represented by a color
	std::vector<TrafficLight> m_trafficLights;

	//and every entry road has its assigned REFERENCE to a traffic light (yes, a reference to a bool)
	//needed because two roads can share the same traffic light
	std::map<const RoadObjectClass*, TrafficLight*> m_lightsOfRoads;
};

#endif // TRAFFICLIGHTCROSSROAD_HPP

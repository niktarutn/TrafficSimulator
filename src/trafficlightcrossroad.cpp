#include "./include/trafficlightcrossroad.hpp"


/*-----------------------------------------------------------------------------
 * For the description, please see the include file
 *-----------------------------------------------------------------------------*/

const double TrafficLightCrossroad::tickTime{ 0.45 };
const double TrafficLightCrossroad::angleDifference{ 0.15 };
const double TrafficLightCrossroad::defaultTrafficLightTime{ 30.00 };

TrafficLightCrossroad::TrafficLightCrossroad( int x, int y, double trafficLightTimeInSeconds ) : CrossroadClass( x, y ),
	m_trafficLightTime{ static_cast<std::size_t>( trafficLightTimeInSeconds / tickTime ) }, m_lightCounter{ 0 }
{
	m_trafficLights.resize( 0 );
    //ctor
}

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  TrafficLightCrossroad::performTimeStep()
 *  Description:  An override of the superclass' function that does exactly the same,
 *  but in addition increases the green-light-time counter and switches the lights
 *  when it reaches the limit
 * =====================================================================================
 */
	void
TrafficLightCrossroad::performTimeStep()
{
		CrossroadClass::performTimeStep();
		/*-----------------------------------------------------------------------------
		 *when it is the time to switch the lights, do that for all traffic lights and
		 *reset the counter, however, sometimes there may be no traffic lights
		 *due to a user input error
		 *-----------------------------------------------------------------------------*/
		if ( ++m_lightCounter > m_trafficLightTime && m_trafficLights.size() != 0 ) {
			//search for the only green light
			auto it { std::find_if( m_trafficLights.begin(), m_trafficLights.end(), []( const TrafficLight& a ) -> bool{
					return a.color;
					} ) };
			//if it is the last one, or there are no green ligths, now the first one should be green
			if ( m_trafficLights.at( m_trafficLights.size() - 1 ).color ) {
				m_trafficLights.at( m_trafficLights.size() - 1 ).color = false;
				m_trafficLights.at( 0 ).color = true;
			}
			//otherwise, the next one should be green
			else if ( it == m_trafficLights.end() ){
				m_trafficLights.at( 0 ).color = true;
			}
			else {
				it->color = false;
				( ++it )->color = true;
			}
			m_lightCounter = 0;
		}
}		/* -----  end of function TrafficLightCrossroad::performTimeStep()  ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  TrafficLightCrossroad::addEntryAngle
 *  Description:  An override of the base function, because every time an angle is added
 *  it is necessary to assign a relevant traffic light to the road with this angle
 * =====================================================================================
 */
	void
TrafficLightCrossroad::addEntryAngle ( const RoadObjectClass* ptrToEntryRoad, double angle )
{
	CrossroadClass::addEntryAngle( ptrToEntryRoad, angle );

	/*
	 * ===  FUNCTION  ======================================================================
	 *         Name:  checkRoadAngle
	 *  Description:  A lambda that takes a pair and checks if there is a road which has
	 *  the angle currentroadAngle + PI +/- angleDifference
	 *
	 * =====================================================================================
	 */
	auto checkRoadAngle
	{
		[ ptrToEntryRoad, this ] ( const std::pair<const RoadObjectClass*, bool>& element ) -> bool
		{
			return
				( m_entryAngles[ ptrToEntryRoad ] <= m_entryAngles[ element.first ] + PI + angleDifference  &&
				m_entryAngles[ ptrToEntryRoad ] >= m_entryAngles[ element.first ] + PI - angleDifference ) ||
				( m_entryAngles[ ptrToEntryRoad ] <= m_entryAngles[ element.first ] - PI + angleDifference  &&
				m_entryAngles[ ptrToEntryRoad ] >= m_entryAngles[ element.first ] - PI - angleDifference );
		}		/* -----  end of function checkRoadAngle  ----- */
	};

	//first, let's see if there already is a road opposite to ours
	//if yes, then it has the same traffic light
	auto it{ std::find_if( m_lightsOfRoads.begin(), m_lightsOfRoads.end(), checkRoadAngle ) };
	//if there is no such a road
	if ( it == m_lightsOfRoads.end() ) {
		//add a new traffic light for our road
		m_trafficLights.push_back( TrafficLight() );
		m_trafficLights[ m_trafficLights.size() - 1 ].color = false;
		m_lightsOfRoads[ ptrToEntryRoad ] = &m_trafficLights[ m_trafficLights.size() - 1 ];
	}
	//if there is such a road, we can assign the same traffic light to ours
	else {
		m_lightsOfRoads[ ptrToEntryRoad ] = m_lightsOfRoads[ it->first ];
	}

	//now all the traffic lights except the first must be red
	m_trafficLights.at( 0 ).color = true;
}		/* -----  end of function TrafficLightCrossroad::addEntryAngle  ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  TrafficLightCrossroad::checkRightToGo
 *  Description:  The required override
 * =====================================================================================
 */
	bool
TrafficLightCrossroad::checkRightToGo ( const RoadObjectClass* ptrToEntry, RoadObjectClass* ptrToExit )
{
    /*
    if (!m_lightsOfRoads.at( ptrToEntry )->color){
        std::cout << "Traffic light forbids to go\n";
    }
    */
	return m_lightsOfRoads.at( ptrToEntry )->color;
	//return false;

}		/* -----  end of function TrafficLightCrossroad::checkRightToGo  ----- */

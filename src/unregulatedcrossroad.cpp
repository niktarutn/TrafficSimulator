#include "./include/unregulatedcrossroad.hpp"

UnregulatedCrossroad::UnregulatedCrossroad( int x, int y ) : CrossroadClass( x, y )
{
    //ctor
}


/*
 * ===  FUNCTION  ======================================================================
 *         Name:  UnregulatedCrossroad::checkRightToGo
 *  Description:  Uses the right hand rule to define if the car can go
 * =====================================================================================
 */
	bool
UnregulatedCrossroad::checkRightToGo ( const RoadObjectClass* ptrToEntry, RoadObjectClass* ptrToExit )
{
	//firstly, create two new angle maps where the entry road has the angle zero
	//and other roads are rotated accordingly
	std::map<const RoadObjectClass*, double> localEntryAngles{};
	std::map<const RoadObjectClass*, double> localExitAngles{};

	/*
	 * ===  FUNCTION  ======================================================================
	 *         Name:  defineAngle
	 *  Description:  A labmda that returns the rotated angle with respect to the entry
	 *  road
	 * =====================================================================================
	 */
	auto
		defineAngle
		{
			[ ptrToEntry, this ]( double angle ) -> double
			{
				//if a road angle is smaller or equal than the one of the entry road
				//it has a new value of 2*PI - entryAngle + road angle
				if ( angle <= m_entryAngles[ ptrToEntry ] ) {
					return 2 * PI - m_entryAngles[ ptrToEntry ] + angle;
				}
				//if the angle is bigger, then the angle is road angle - entryAngle
				else {
					return angle - m_entryAngles[ ptrToEntry ];
				}
			}
		};		/* -----  end of function defineAngle  ----- */

	//let's rotate the entry road angles...
	//... for the entry roads
	for ( auto& element : m_entryAngles ){
		localEntryAngles.insert( std::make_pair( element.first, defineAngle( element.second ) ) );
	}
	//the algorithm has assinged the angle 360 for the entry road itself, should be 0
	localEntryAngles[ ptrToEntry ] = 0.00;
	//... for the exit
	for ( auto& element : m_exitAngles ){
		localExitAngles.insert( std::make_pair( element.first, defineAngle( element.second ) ) );
	}

	//initially, it is allowed for a car to go
	bool canGo{ true };

	//unless in any of the entry roads from the right...
	for ( const auto& element : localEntryAngles ){
		//we are interested only in the road with the angle less than our desired exit road
		//in other words, from the right
		//and if there is a car standing
		//and if it's not our road of consideration itself, otherwise it looses the priority battle to itsef
		if ( element.second < localExitAngles[ ptrToExit ] && m_entryRoads[ element.first ] && element.first != ptrToEntry ) {
			//if it does not have the triangle and we do
			if ( ptrToEntry->hasTriangle() && !element.first->hasTriangle() ) {
				canGo = false;
				break;
			}
			//if it has the triangle and we do not
			if ( !ptrToEntry->hasTriangle() && element.first->hasTriangle() ) {
				continue;
			}
			//finaly, if the car in the crossroad wants to turn to the exit road
			//with a bigger or equal anlge
			if ( localExitAngles[ m_entryRoads[ element.first ]->FindNextRoad( this ) ] >= localExitAngles[ ptrToExit ] ) {
				canGo = false;
				break;
			}
		}
	}
	return canGo;
}		/* -----  end of function UnregulatedCrossroad::checkRightToGo  ----- */

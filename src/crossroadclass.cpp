#include "./include/crossroadclass.hpp"


/*-----------------------------------------------------------------------------
 * For the description, see the include file
 * contact info - Alexey Serous
 *-----------------------------------------------------------------------------*/
std::size_t CrossroadClass::numOfCrossroads{ 0 };

CrossroadClass::CrossroadClass( int x, int y ) :
	m_x{ x }, m_y{ y }
{
	id_ = ++numOfCrossroads;
    //ctor
}

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  takeVehicle
 *  Description:  takes a Vehicle* from an entry road, checks if there is space
 *  and decides whether to accept it. A Building may use nullptr for RoadObjectClass*
 *  argument
 * =====================================================================================
 */
	bool
CrossroadClass::takeVehicle ( Vehicle* ptrToCar, const RoadObjectClass* ptrToRoadObject )
{
	if ( m_entryRoads[ ptrToRoadObject ] == nullptr ) {
		m_entryRoads[ ptrToRoadObject ] = ptrToCar;
		return true;
	}
	else {
		return false;
	}
}		/* -----  end of function takeVehicle  ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  CrossroadClass::performTimeStep
 *  Description: Throws the NavigatorException()
 * =====================================================================================
 */
	void
CrossroadClass::performTimeStep ()
{
	//check what cars have the right to go
	std::map<const RoadObjectClass*, bool> hasRightToGo{};
	for ( const auto& element : m_entryRoads ){
		//but only if there is a car standing
		if ( element.second ) {
			//the car must not have nullptr as its next destination
			if( !element.second->FindNextRoad( this ) ){
				throw NavigatorException( this );
			}
				hasRightToGo[ element.first ] = checkRightToGo( element.first, element.second->FindNextRoad( this ) );
		}
	}

	//sometimes, no cars are allowed to go because they all have an obstacle from the right
	//in this case the first one tries
	/*auto it{ std::find_if( hasRightToGo.begin(), hasRightToGo.end(), []( auto& a ) -> bool
			{
			return a.second;
			} ) };
	if ( it == hasRightToGo.end() ) {
		hasRightToGo.begin()->second = true;
	}*/

	//for every car that has the right to go
	for ( auto& element : m_entryRoads ){
		//if there is a car...
		if ( element.second ) {
			//... and it is allowed to go
			if ( hasRightToGo[ element.first ] ) {
				 //and if the exit road accepts it
				 if ( element.second->FindNextRoad( this )->takeVehicle( element.second, this ) ){
					element.second = nullptr;
				 } else {
				 //std::cout << "Cannot go\n";
				 }
			}
		}
	}
}		/* -----  end of function CrossroadClass::performTimeStep  ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  CrossroadClass::addEntryRoad
 *  Description:  does what is specified by the name, returns true if succeeded
 * =====================================================================================
 */
	bool
CrossroadClass::addEntryRoad ( const RoadObjectClass* ptrToEntryRoad )
{
	//add an entry road with no car currently
	//m_entryRoads.insert( std::make_pair( ptrToEntryRoad, nullptr ) );
	m_entryRoads[ ptrToEntryRoad ] = nullptr;
	return true;
}		/* -----  end of function CrossroadClass::addEntryRoad  ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  CrossroadClass::addExitRoad
 *  Description:  does what is described in the name
 * =====================================================================================
 */
	bool
CrossroadClass::addExitRoad ( RoadObjectClass* ptrToExitRoad )
{
	m_exitRoads.push_back( ptrToExitRoad );
	return true;
}		/* -----  end of function CrossroadClass::addExitRoad  ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  CrossroadClass::getX
 *  Description:  returns the coordinate
 * =====================================================================================
 */
	int
CrossroadClass::getX ()
{
	return m_x;
}		/* -----  end of function CrossroadClass::getX  ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  CrossroadClass::getY
 *  Description:  returns the coordinate
 * =====================================================================================
 */
	int
CrossroadClass::getY ()
{
	return m_y;
}		/* -----  end of function CrossroadClass::getY  ----- */


bool CrossroadClass::operator==(const CrossroadClass& a){
	bool isEqual = a.m_x == m_x && a.m_y == m_y;
	return isEqual;
}

bool CrossroadClass::operator==(CrossroadClass& a){
	bool isEqual = a.m_x == m_x && a.m_y == m_y;
	return isEqual;
}

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  CrossroadClass::addEntryAngle
 *  Description:  For the RoadLineClass, add the angle for a road
 * =====================================================================================
 */
	void
CrossroadClass::addEntryAngle ( const RoadObjectClass* ptrToEntryRoad, double angle )
{
	m_entryAngles.insert( std::make_pair( ptrToEntryRoad, angle ) );
}		/* -----  end of function CrossroadClass::addEntryAngle  ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  CrossroadClass::addExitAngle
 *  Description:  For the RoadLineClass, add the angle for a road
 * =====================================================================================
 */
	void
CrossroadClass::addExitAngle ( RoadObjectClass* ptrToExitRoad, double angle )
{
	m_exitAngles.insert( std::make_pair( ptrToExitRoad, angle ) );
}		/* -----  end of function CrossroadClass::addExitAngle  ----- */

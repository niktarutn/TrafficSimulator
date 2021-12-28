#include "./include/buildingexitcrossroad.hpp"

/*-----------------------------------------------------------------------------
 * For the description see the header file
 *-----------------------------------------------------------------------------*/
unsigned int BuildingExitCrossroad::carsLeftHome{ 0 };

BuildingExitCrossroad::BuildingExitCrossroad( int x, int y ) :
	CrossroadClass( x, y )
{
    //ctor
}

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  BuildingExitCrossroad::checkRightToGo
 *  Description:  The entry roads have the priority, cars coming out of buildings have
 *  to wait. Since there can be many entry roads, the priotiy between them is not
 *  estimated, always true. Not recommended to have more than two entry roads because of this
 * =====================================================================================
 */
	bool
BuildingExitCrossroad::checkRightToGo ( const RoadObjectClass* ptrToEntry, RoadObjectClass* ptrToExit )
{
	//if a car comes from one of the entry roads, it is allowed to go
	auto it{ std::find( m_realEntryRoads.begin(), m_realEntryRoads.end(), ptrToEntry ) };
	if ( it != m_realEntryRoads.end() ) {
		return true;
	}
	//else, we need to check if there is a car in any of entry roads
	bool carPresent{ false };
	for ( auto element : m_realEntryRoads ){
		if ( m_entryRoads.at( element ) ) {
			carPresent = true;
			break;
		}
	}
	//so, if there is a car anywhere, return false
	return !carPresent;
}		/* -----  end of function BuildingExitCrossroad::checkRightToGo  ----- */

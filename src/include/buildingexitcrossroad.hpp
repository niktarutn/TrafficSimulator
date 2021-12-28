#ifndef BUILDINGEXITCROSSROAD_HPP
#define BUILDINGEXITCROSSROAD_HPP

#include "crossroadclass.hpp"


/*-----------------------------------------------------------------------------
 * A crossroad that connects only two rows (enter and exit), in addition
 * to several buildings. A Car coming from a building has to wait for an
 * empty entry road.
 *
 * Contact info - Alexey
 *-----------------------------------------------------------------------------*/

class BuildingExitCrossroad : public CrossroadClass
{
    public:
        BuildingExitCrossroad( int x, int y );
        static unsigned int carsLeftHome;

	/*-----------------------------------------------------------------------------
	 * Copy constructors to be forbidden 
	 *-----------------------------------------------------------------------------*/
	BuildingExitCrossroad( const BuildingExitCrossroad& a ) = delete;

	~BuildingExitCrossroad() override = default; //destructor

	BuildingExitCrossroad& operator = ( const BuildingExitCrossroad& a ) = delete;
    protected:

    private:
	virtual bool checkRightToGo
		( const RoadObjectClass* ptrToEntry, RoadObjectClass* ptrToExit ) override;

};

#endif // BUILDINGEXITCROSSROAD_HPP

#ifndef UNREGULATEDCROSSROAD_HPP
#define UNREGULATEDCROSSROAD_HPP

#include "crossroadclass.hpp"

/*-----------------------------------------------------------------------------
 *  A crossroad that has no traffic lights and uses the right hand rule to
 *  decide the priority.
 *  Contact info - Alexey
 *-----------------------------------------------------------------------------*/

class UnregulatedCrossroad : public CrossroadClass
{
    public:
        UnregulatedCrossroad( int x, int y );

	/*-----------------------------------------------------------------------------
	 * Copy constructors to be forbidden 
	 *-----------------------------------------------------------------------------*/
	UnregulatedCrossroad( const UnregulatedCrossroad& a ) = delete;

	~UnregulatedCrossroad() override = default; //destructor

	UnregulatedCrossroad& operator = ( const UnregulatedCrossroad& a ) = delete;

    protected:

    private:

	bool checkRightToGo
		( const RoadObjectClass* ptrToEntry, RoadObjectClass* ptrToExit ) override;
};

#endif // UNREGULATEDCROSSROAD_

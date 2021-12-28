#ifndef CROSSROADCLASS_H
#define CROSSROADCLASS_H

#include <map>
#include <utility>
#include <vector>
#include <algorithm>
#include <iostream>

#include "roadobjectclass.hpp"

/*
 * =====================================================================================
 *        Class:  CrossroadClass
 *  Description:  The class acts as a moderator between the roads
 *  Consists of two containers
 *  1) <RoadObjectClass*, Vehicle*> for entry roads
 *  2) <RoadObjectClass*> for exit roads
 *  If there is currently no vehicle standing on the position of entry roads, then it is nullptr
 *
 *
 *  contact information - Alexey Serous
 * =====================================================================================
 */

class CrossroadClass : public RoadObjectClass
{
    public:
        CrossroadClass( int x, int y );

	/*-----------------------------------------------------------------------------
	 * Copy constructors to be forbidden 
	 *-----------------------------------------------------------------------------*/
	CrossroadClass( const CrossroadClass& a ) = delete;

	virtual ~CrossroadClass() = default; //destructor

	bool takeVehicle( Vehicle* ptrToCar, const RoadObjectClass* ptrToRoadObject ) override;

	void performTimeStep() override;

	//for the RoadLineClass, add entry and exit roads
	bool addEntryRoad ( const RoadObjectClass* ptrToEntryRoad );
	bool addExitRoad ( RoadObjectClass* ptrToExitRoad );
	//for the RoadLineClass, define angles for entry and exit roads. Is virtual
	//for the TrafficLightCrossroad
	virtual void addEntryAngle ( const RoadObjectClass* ptrToEntryRoad, double angle );
	void addExitAngle ( RoadObjectClass* ptrToExitRoad, double angle );

	//used only in a building exit crossroad, added here so that a road can set a value
	void setRealEntryRoad( RoadObjectClass* ptrToEntry ){
		m_realEntryRoads.push_back( ptrToEntry );
	}
	//get coordinates
	int getX();
	int getY();

	//forbid copy assignment
	CrossroadClass& operator = ( const CrossroadClass& a ) = delete;

	bool operator==(const CrossroadClass& a);

	bool operator==(CrossroadClass& a);

	friend std::ostream &operator<<(std::ostream& out, const CrossroadClass& a) {
    out << "Crossroad with id " << a.id_;
    return out;
}

    protected:

	//delete the road-only function
	bool hasTriangle() const = delete;

	//entry and exit roads
	std::map<const RoadObjectClass*, Vehicle*> m_entryRoads;
	std::vector<RoadObjectClass*> m_exitRoads;

	//entry and exit roads angles
	std::map<const RoadObjectClass*, double> m_entryAngles;
	std::map<const RoadObjectClass*, double> m_exitAngles;

	//used only in a building exit crossroad, added here so that a road can set a value
	std::vector<RoadObjectClass*> m_realEntryRoads;

    private:

	//the main function of every particular crossroad type, defines if it is ok
	//for a car to go
	virtual bool checkRightToGo
		( const RoadObjectClass* ptrToEntry, RoadObjectClass* ptrToExit ) = 0;

	//coordinates
	int m_x;
	int m_y;
	std::size_t id_;

	//counter
	static std::size_t numOfCrossroads;

};

#endif // CROSSROADCLASS_H

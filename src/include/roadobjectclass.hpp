#ifndef ROADOBJECTCLASS_H
#define ROADOBJECTCLASS_H

#include "exceptions.hpp"
#include "Vehicle.hpp"
#include <iostream>

const double PI{ 3.14 };
/*
 * =====================================================================================
 *        Class:  RoadObjectClass
 *  Description:  An interface to be inherited by the RoadLineClass and CrossroadClass
 *  contact information - Alexey Serous
 * =====================================================================================
 */

class RoadObjectClass
{
	public:

		/* ====================  LIFECYCLE     ======================================= */
		RoadObjectClass ( bool hasTriangle = false );                             /* constructor */

		/*-----------------------------------------------------------------------------
		 * Copy constructors to be forbidden 
		 *-----------------------------------------------------------------------------*/
		RoadObjectClass( const RoadObjectClass& a ) = delete;

		virtual ~RoadObjectClass() = default; //destructor

		/* ====================  ACCESSORS     ======================================= */
		bool hasTriangle() const;

		/* ====================  MUTATORS      ======================================= */

		virtual bool takeVehicle( Vehicle* ptrToCar, const RoadObjectClass* ptrToRoadObject ) = 0;

		virtual void performTimeStep() = 0;

		/* ====================  OPERATORS     ======================================= */
		RoadObjectClass& operator = ( const RoadObjectClass& a ) = delete;

	protected:
		/* ====================  METHODS       ======================================= */

		/* ====================  DATA MEMBERS  ======================================= */

	private:
		/* ====================  METHODS       ======================================= */

		/* ====================  DATA MEMBERS  ======================================= */
		bool m_hasTriangle;

}; /* -----  end of class RoadObjectClass  ----- */

#endif // ROADOBJECTCLASS_H

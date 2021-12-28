#ifndef CITY_OBJECT_HPP
#define CITY_OBJECT_HPP

#include <utility>
/*
 * =====================================================================================
 *        Class:  CityObject
 *  Description:  A CityObject class, to be inherited by every object in a city.
 * Implementation of all functions to be done by a person responsible for a
 * child class.
 * Contact info - Alexey.
 * =====================================================================================
 */
class CityObject
{
	public:
		/* ====================  LIFECYCLE     ======================================= */
		CityObject (){};                             /* constructor */

		/* ====================  ACCESSORS     ======================================= */

		/* ====================  MUTATORS      ======================================= */

		/* ====================  OPERATORS     ======================================= */

	protected:
		/* ====================  METHODS       ======================================= */

		//get coordinates separately
		int getX() { return m_x; }
		int getY() { return m_y; }
		//get coordinates as a pair
		std::pair<int, int> getCoordinates();
		//set coordinates, delete for buildings
		virtual bool setCoordinates( int x, int y );

		/* ====================  DATA MEMBERS  ======================================= */

	private:
		/* ====================  METHODS       ======================================= */

		/* ====================  DATA MEMBERS  ======================================= */
		//coordinates in meters, constant for buildings and rodas, variable for cars
		int m_x{};
		int m_y{};

}; /* -----  end of class CityObject  ----- */

#endif

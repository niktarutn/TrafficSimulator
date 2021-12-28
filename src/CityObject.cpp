#include "./include/CityObject.hpp"

/*
 * =====================================================================================
 *
 *       Filename:  CityObject.cpp
 *
 *    Description:  A CityObject class, to be inherited by every object in a city.
 * Implementation of all functions to be done by a person responsible for a
 * child class.
 * Contact info - Alexey.
 *
 *        Version:  0.01
 *        Created:  11/03/2021 09:06:25 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Alexey Serous (), 
 *   Organization:  Aalto
 *
 * =====================================================================================
 */


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  CityObject::getCoordinates
 *  Description:  get coordinates as a pair
 * =====================================================================================
 */
	std::pair<int, int>
CityObject::getCoordinates ()
{
	return std::make_pair( m_x, m_y );
}		/* -----  end of function CityObject::getCoordinates  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  CityObject::setCoordinates
 *  Description:  set coordinates, delete for buildings
 * =====================================================================================
 */
	bool
CityObject::setCoordinates ( int x, int y )
{
	m_x = x;
	m_y = y;
	return true;
}		/* -----  end of function CityObject::setCoordinates  ----- */

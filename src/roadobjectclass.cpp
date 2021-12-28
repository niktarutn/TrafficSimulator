#include "./include/roadobjectclass.hpp"

/*-----------------------------------------------------------------------------
 * For the class description see the include file
 * Contact info - Alexey Serous
 *-----------------------------------------------------------------------------*/

RoadObjectClass::RoadObjectClass( bool hasTriangle ) : m_hasTriangle{ hasTriangle }
{
    //ctor
}

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  RoadObjectClass::hasTriangle
 *  Description:  used only for the roads, to be deleted in other classes
 * =====================================================================================
 */
	bool
RoadObjectClass::hasTriangle () const
{
	return m_hasTriangle;
}		/* -----  end of function RoadObjectClass::hasTriangle  ----- */

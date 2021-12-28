#include "./include/cityclass.hpp"

/*-----------------------------------------------------------------------------
 *  For the description see the include header file
 *-----------------------------------------------------------------------------*/

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  CityClass::CityClass
 *  Description:  A constructor that takes the file name as a parameter
 *  1) Imports the crossroads
 *  2) Imports the roads
 *  3) Imports somethings else, please start from here
 * =====================================================================================
 */
CityClass::CityClass(std::string fileName) : m_fileName{ fileName }
{

	/*
	 * ===  FUNCTION  ======================================================================
	 *         Name:  lookupCrossroad
	 *  Description:  a lambda that takes a string and checks if there
	 *  is a key value with the desired string in crossroads
	 * =====================================================================================
	 */
	auto
		lookupCrossroad
		{
			[ this ]( std::string a ) -> bool
			{
				auto it{ std::find_if( m_crossroads.begin(), m_crossroads.end(), [ a ]( auto& element ) -> bool{
						return element.first == a;
						} ) };
				return it != m_crossroads.end();
			}
		};		/* -----  end of function lookupCrossroad  ----- */

	std::ifstream input{ fileName };
	if ( !input ) {
		std::cerr << "Error! The file " << fileName << " cannot be accessed\n";
	}

	std::string fileLine{};
	//import the crossroads
	int x{};
	int y{};
	char crossRoadType{};
	std::string objectName{};
	std::stringstream parameters{};
	double trafficLightTime{};
	//get to the file section with crossroads
	while ( fileLine != "CROSSROADS" && !input.eof() ) {
		std::getline( input, fileLine );
	}

	//import the first crossroad
	std::getline( input, fileLine );
	if ( input.eof() ) {
		throw UserInputException( "Error, the input file does not contain \"CROSSROADS\" section!" );
	}
	//start constructing of the crossroad container
	while ( fileLine != "ROADS" && !input.eof() ) {
		parameters.str( fileLine );
		parameters >> crossRoadType >> objectName >> x >> y >> trafficLightTime;
		//depending on the type (Unregulated, building exit, etc...)
		if ( lookupCrossroad( objectName ) ) {
			throw UserInputException( "Error! A dublicated crossroad name in the input file." );
		}
		switch ( crossRoadType ){
			case 'U':
				m_crossroads.insert(
						std::make_pair( objectName, new UnregulatedCrossroad{ UnregulatedCrossroad( x, y ) } )
						);
				break;
			case 'B':
				m_crossroads.insert(
						std::make_pair( objectName, new BuildingExitCrossroad{ BuildingExitCrossroad( x, y ) } )
						);
				m_buildingExitCrossroadsNames.push_back( objectName );
				break;
			case 'T':
				m_crossroads.insert(
						std::make_pair( objectName, new TrafficLightCrossroad{ TrafficLightCrossroad( x, y,
						       ( trafficLightTime == 0 ? TrafficLightCrossroad::defaultTrafficLightTime : trafficLightTime )
						       ) } ) );
				break;
			default:
				throw UserInputException( "Error! An incorrect cross road type was specified in the input file!" );
		}
		parameters.clear();
		trafficLightTime = 0;
		std::getline( input, fileLine );
	}
	if ( input.eof() ) {
		throw UserInputException( "Error, the input file does not contain \"ROADS\" section!" );
	}
	//import the roads
	std::string start{};
	std::string end{};
	std::string parameter1{};
	std::string parameter2{};
	std::getline( input, fileLine );
	std::stringstream convert{};
	std::size_t maxSpeed{ 0 };
	bool hasTriangle{ false };

	/*
	 * ===  FUNCTION  ======================================================================
	 *         Name:  isNumber
	 *  Description:  takes a string and validates whether it is a number (true)
	 *  or does it contain letters (false)
	 * =====================================================================================
	 */
	auto
		isNumber
		{ []( std::string a ) -> bool
			{
				bool returnValue{ a.size() > 0 };
				for( auto element : a ){
					switch( element ){
						case '0':
						case '1':
						case '2':
						case '3':
						case '4':
						case '5':
						case '6':
						case '7':
						case '8':
						case '9':
							break;
						default: returnValue = false;
					}
				}
				return returnValue;
			}
		};		/* -----  end of function isNumber  ----- */

	while ( fileLine != "BUILDINGS" && !input.eof() ) {
		parameters.str( fileLine );
		parameters >> objectName >> start >> end >> parameter1 >> parameter2;
		if ( !lookupCrossroad( start ) || !lookupCrossroad( end ) ) {
			throw UserInputException( "Error! A road was specified to have a non-existing crossroad as start or end." );
		}
		if ( parameter1 == "HASTRIANGLE" || parameter2 == "HASTRIANGLE" ) {
			hasTriangle = true;
		}
		else {
			hasTriangle = false;
		}
		if ( isNumber( parameter1 ) ) {
			convert << parameter1;
			convert >> maxSpeed;
		}
		if ( isNumber( parameter2 ) ) {
			convert << parameter2;
			convert >> maxSpeed;
		}
		m_roads.push_back(
				std::make_pair( objectName, new RoadLineClass{ RoadLineClass( m_crossroads.at( start ), m_crossroads.at( end ),
						hasTriangle, maxSpeed ) } )
			      );

		/*-----------------------------------------------------------------------------
		 * insert one more road for the reverse direction
		 *-----------------------------------------------------------------------------*/
		objectName += "_reverse";
		m_roads.push_back(
				std::make_pair( objectName, new RoadLineClass{ RoadLineClass( m_crossroads.at( end ), m_crossroads.at( start ),
						hasTriangle, maxSpeed ) } )
			      );

		std::getline( input, fileLine );
		parameters.clear();
		convert.clear();
		parameter1 = "";
		parameter2 = "";
		hasTriangle = false;
		maxSpeed = 40;
	}

	if ( input.eof() ) {
		throw UserInputException( "Error, the input file does not contain \"BUILDINGS\" section!" );
	}

	std::getline( input, fileLine );

	std::string buildingType{};
	std::string exitCrossroad{};
	int capacity{};
	//start constructing of the building container
	while ( fileLine != "NEXT_SETTING_NAME" && !input.eof() ) {
		parameters.str( fileLine );
		parameters >> buildingType >> objectName >> exitCrossroad >> capacity;
		if ( std::find( m_buildingExitCrossroadsNames.begin(), m_buildingExitCrossroadsNames.end(), exitCrossroad ) ==
		  m_buildingExitCrossroadsNames.end() ) {
			throw UserInputException( "Error! A building was specified to have a non-existing crossroad as an exit crossroad." );
		}
		//depending on the type (Recreational, Residential...)
		if (buildingType == "REC"){
			m_RECbuildings.push_back(
					std::make_pair( objectName, new RecreationalBuilding{ RecreationalBuilding( m_crossroads[exitCrossroad], capacity ) } )
			);
		}else if (buildingType=="RES"){
			m_RESbuildings.push_back(
					std::make_pair( objectName, new ResidentialBuilding{ ResidentialBuilding( m_crossroads[exitCrossroad], capacity ) } )
					);
		}else if (buildingType == "IND"){
			m_INDbuildings.push_back(
					std::make_pair( objectName, new IndustrialBuilding{ IndustrialBuilding( m_crossroads[exitCrossroad], capacity ) } )
					);
		}else if (buildingType == "COM"){
			m_COMbuildings.push_back(
					std::make_pair( objectName, new CommercialBuilding{ CommercialBuilding( m_crossroads[exitCrossroad], capacity ) } )
					);
		}else{
		throw UserInputException("Error! An incorrect building type specified in the input file");
		}
		parameters.clear();
		std::getline( input, fileLine );
	}
}
std::map<std::string,CrossroadClass*>& CityClass::GetCrossroads(){
	return m_crossroads;
}
std::vector<std::pair<std::string,RoadLineClass*>>& CityClass::GetRoads(){
	return m_roads;
}
std::vector<std::pair<std::string,Building*>>& CityClass::GetRESBuildings(){
	return m_RESbuildings;
}
std::vector<std::pair<std::string,Building*>>& CityClass::GetRECBuildings(){
	return m_RECbuildings;
}
std::vector<std::pair<std::string,Building*>>& CityClass::GetINDBuildings(){
	return m_INDbuildings;
}
std::vector<std::pair<std::string,Building*>>& CityClass::GetCOMBuildings(){
	return m_COMbuildings;
}

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  CityClass::~CityClass
 *  Description:  The destructor
 * =====================================================================================
 */
CityClass::~CityClass ()
{
	//delete all the crossroads
	for( auto& element : m_crossroads ){
		delete element.second;
		element.second = nullptr;
	}

	//delete all the roads
	for( auto& element : m_roads ){
		delete element.second;
		element.second = nullptr;
	}

	//delete all the buildings
	for( auto& element : m_RECbuildings ){
		delete element.second;
		element.second = nullptr;
	}

	for( auto& element : m_RESbuildings ){
		delete element.second;
		element.second = nullptr;
	}

	for( auto& element : m_INDbuildings ){
		delete element.second;
		element.second = nullptr;
	}

	for( auto& element : m_COMbuildings ){
		delete element.second;
		element.second = nullptr;
	}
}		/* -----  end of function CityClass::~CityClass  ----- */

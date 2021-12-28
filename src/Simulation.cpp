#include "./include/Simulation.hpp"

#include <iterator>
#include <iostream>
#include <fstream>
#include <cmath>
#include <utility>


/*-----------------------------------------------------------------------------
 * Alexey's tests. Commented std::cout At tick, ticks fine, not needed now
 * because it occupies other info output by the console.
 * Added the console output of the car number for every road after every tick, if there
 * are cars, line 100
 *-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * Alexey's edit: added exceptions, so that it is possible to figure out
 * where the error happened
 *-----------------------------------------------------------------------------*/

Simulation::Simulation(CityClass* city, unsigned int npeople, double endtime,std::string outputfile,std::string RoadToAnalyze){ //outputfile
    city_ = city;
    npeople_ = npeople;
    endtime_ = endtime;
    outputfile_ = outputfile;
	RoadToAnalyze_ = RoadToAnalyze;
}


/*
* void Simulation::Init() initializes npeople number of people in random location in given city.
*/

void Simulation::Init(){

    std::vector<std::pair<std::string,RoadLineClass*>> roadMap = city_->GetRoads();

    std::map<std::string,CrossroadClass*> crossroadClassMap = city_->GetCrossroads();

    std::vector<RoadLineClass*> roads;
    for(std::vector<std::pair<std::string,RoadLineClass*>>::iterator it = roadMap.begin(); it != roadMap.end(); ++it) {
    roads.push_back(it->second);
    }

    std::vector<CrossroadClass*> crossRoads;
    for(std::map<std::string,CrossroadClass*>::iterator it = crossroadClassMap.begin(); it != crossroadClassMap.end(); ++it) {
    crossRoads.push_back(it->second);
    }

    Navigator* navigator= new Navigator(roads, crossRoads);

    std::vector<std::pair<std::string,Building*>>  residentBuildings = city_ -> GetRESBuildings();
    std::vector<std::pair<std::string,Building*>>  recreationalBuildings = city_ -> GetRECBuildings();
    std::vector<std::pair<std::string,Building*>>  commercialBuildings = city_ -> GetCOMBuildings();
    std::vector<std::pair<std::string,Building*>>  industrialBuildings = city_ -> GetINDBuildings();

    int peopleToSettle = npeople_;
    while (peopleToSettle > 0) {

        //TODO: THINK OF SCENARIO WHEN MAXIMUM BUILDING'S CAPACITY IS REACHED
        int randomRESBuildingIndex = rand() % residentBuildings.size();
        int randomRECBuildingIndex = rand() % recreationalBuildings.size();
        int randomINDBuildingIndex = rand() % industrialBuildings.size();
        int randomCOMBuildingIndex = rand() % commercialBuildings.size();

        int carSize =  1; // rand() % 5 + 1; CARS WILL HAVE SIZE OF ONE ROAD SLOT (5 m) FOR NOW
        bool fitting = residentBuildings[randomRESBuildingIndex].second->takeVehicle(new Car(carSize), nullptr);
        if (fitting) {
            Building* home = residentBuildings[randomRESBuildingIndex].second;
            Building* recreational = recreationalBuildings[randomRECBuildingIndex].second;
            Building* commercial = commercialBuildings[randomCOMBuildingIndex].second;
            Building* work = industrialBuildings[randomINDBuildingIndex].second;
            Person* newperson = new Person(navigator, home, recreational, commercial, work);
            residentBuildings[randomRESBuildingIndex].second->TakePerson(newperson);

            people_.push_back(newperson);
        }
        peopleToSettle --;

    }
}

void Simulation::Simulate(){
	double ticksInHour = 8000; // 8000 ticks in an hour
	unsigned int maxticks = ticksInHour*endtime_;
    // double tick = 0.45; // seconds NOT NEEDED

	// Open outputfile MAYBE DO SOME MORE EXCEPTIONHANDLING HERE
	std::ofstream outfile;
    outfile.open (outputfile_);
	if (outfile.fail()){
    	std::cout << "Failed to open outputfile. Please check the path.\n";
	}

	std::cout<<"Simulation in progress..."<<std::endl;

	// Get all roads of the city
	std::vector<std::pair<std::string,RoadLineClass*>> roads = city_->GetRoads();

	// Find the index to RoadToAnalyze
	auto analyze_index = find_if(roads.begin(), roads.end(),[=] (std::pair<std::string,RoadLineClass*> pair){return pair.first == RoadToAnalyze_;}) -roads.begin();
	// Get the maximum capacity of road to analyze
	double maxcapacity = 1.0*roads[analyze_index].second->GetSize();
	// Initialize a vectors for saving histogram values (average amount of cars + number of possible jamticks)
	std::vector<double> histogram1;
	std::vector<int> histogram2;
	int hourlyjamticks = 0;


	// Copy roadnames on the first line of output
	outfile<<"Time"<<",";
	std::vector<std::string> firstline;
	std::transform(roads.cbegin(), roads.cend(),std::back_inserter(firstline),[](std::pair<std::string,RoadLineClass*> pair) {return pair.first; });
	std::copy(firstline.begin(), firstline.end(), std::ostream_iterator<std::string>(outfile, ","));
	outfile << std::endl;

	// At each tick, get the amount of cars on all roads into this
	std::vector<double> newline;

    // At each tick of an hour, sum the amount of cards on each road into this, then average and clear hourly.
    std::vector<double> outputline (roads.size(), 0.0);


    try{
	    for (unsigned int tickindex = 0; tickindex < maxticks; ++tickindex){
			//iterate through crossroads
			for (auto [name, crossroad] : city_->GetCrossroads()){
				crossroad->performTimeStep();
			}
			//iterate through roads
			for (auto [name, road] : city_->GetRoads()){
				road->performTimeStep();
			}
			//iterate through RESbuildings
			for (auto [name, building] : city_->GetRESBuildings()){
				building->performTimeStep();
			}
			//iterate through RECbuildings
			for (auto [name, building] : city_->GetRECBuildings()){
				building->performTimeStep();
			}
			//iterate through INDbuildings
			for (auto [name, building] : city_->GetINDBuildings()){
				building->performTimeStep();
			}
			//iterate through COMbuildings
			for (auto [name, building] : city_->GetCOMBuildings()){
				building->performTimeStep();
			}
			//iterate through people
			for (auto person : people_){
				person->performTimeStep(tickindex);
			}


			// Get the amount of cars on each road
			std::transform(roads.cbegin(), roads.cend(),std::back_inserter(newline),[](std::pair<std::string,RoadLineClass*> pair) {return (double) pair.second->getNumberOfCars(); });

			// Detect possible jam ticks
			if(newline[analyze_index]>=maxcapacity-1){
				hourlyjamticks +=1;
			}

			// Add up to the hourly sum
			std::transform (outputline.begin(), outputline.end(), newline.begin(), outputline.begin(), std::plus<double>());
			newline.clear();

			// hourly averagin
			if(tickindex % ((int) ticksInHour-1) == 0 && tickindex != 0){ //8000 ticks in an hour
				/*WRITE OUTPUTFILE*/
				// absolute time (beginning hour)
				unsigned int hour = tickindex/8000;
				// write the time
				outfile << hour <<",";
				// average the amount of cars
				std::transform (outputline.begin(), outputline.end(),outputline.begin(), [ticksInHour](double &c){ return c/ticksInHour; });
				// copy to outputfile
				std::copy(outputline.begin(), outputline.end()-1, std::ostream_iterator<double>(outfile, ","));
				// copy the last one without a comma and then end line
				outfile << outputline.back() <<std::endl;

				/*SAVE DETAILS OF RoadToAnalyze SEPARATELY*/
				histogram1.push_back(outputline[analyze_index]);
				histogram2.push_back(hourlyjamticks);

				// then clear outputline and jamticks to start a new hour
				std::fill(outputline.begin(), outputline.end(), 0.0);
				hourlyjamticks = 0;

				//Show progress in cout
				std::cout<<"[";
				for (int printhour = 0; printhour<endtime_;printhour++){
					if(printhour<hour){
						std::cout<<"=";
					}else if(printhour==hour){
						std::cout<<">";
					}else{
						std::cout<<" ";
					}
				}
				std::cout<<"]    "<< hour+1 << " hours out of " << endtime_ << " done."<<std::endl;;

			}

			//std::cout<<"At tickindex "<<tickindex<<std::endl;
			/*-----------------------------------------------------------------------------
			* Alexey's test
			*-----------------------------------------------------------------------------*/
			// for ( const auto& element : city_->GetRoads() ){
			// 	if ( element.second->getNumberOfCars() != 0 ){
			// 		std::cout << "The road " << element.first << " has " << element.second->getNumberOfCars() << " cars at tick "
			// 			<< tickindex << std::endl;
			// 	}
			// }

		}
		outfile.close();
    }
	catch ( NavigatorException& e ){
		//find the crossroad that caused an error
		auto it{ std::find_if( city_->GetCrossroads().begin(), city_->GetCrossroads().end(),
				[ &e ]( auto& element ) -> bool
				{
					return element.second == e.getErrorObject();
				} ) };
		std::cout << "Error: " << e.what() <<
			" for the crossroad " << ( it == city_->GetCrossroads().end() ?
			"that cannot be located" : it->first ) << std::endl;
	}
	catch ( BuildingRemovePersonException& e ){
		std::cout << e.what() << std::endl;
	}
	catch ( NullPtrException& e ){
		std::cout << e.what() << '\n' << e.getCustomMessage() << std::endl;
	}
	catch ( UserInputException& e ){
		std::cout << e.what() << e.getCustomMessage() << std::endl;
	}


	/* ################### MAKE AND PRINT HISTOGRAM #########################################*/

	int histogramsize = 20;
	double maxvalue = *std::max_element(histogram1.begin(), histogram1.end());
	//double maxcapacity_double = (double) roads[analyze_index].second->GetSize();
	//int maxcapacity_scaled = std::round((maxcapacity/maxvalue)*histogramsize);

	std::fill_n(std::ostream_iterator<std::string>(std::cout), histogramsize+80, "#");
	std::cout<<std::endl<<"A histogram of the relative amount of cars on "<<RoadToAnalyze_<<std::endl;
	std::fill_n(std::ostream_iterator<std::string>(std::cout), histogramsize+80, "#");
	std::cout<<std::endl<<"Time";
	std::fill_n(std::ostream_iterator<std::string>(std::cout), histogramsize+8, " ");
	std::cout<<"Avg. amount of cars  '%' of max capacity  Possible jamticks detected"<<std::endl;

	for (int hour = 0; hour<endtime_;hour++){

		int printhour = hour%24;
		if(printhour<10){
			std::cout<<"0"<<printhour<<":00"<<" ||";
		}else{
			std::cout<<printhour<<":00"<<" ||";
		}
		int outofmax = (int) std::round((histogram1[hour]/maxvalue)*histogramsize);
		for (int i = 0; i<histogramsize; i++){
			if(outofmax>i){
				std::cout<<"*";
			}else{
				std::cout<<"-";
			}
		}
		std::cout.precision(4);
		std::cout<<std::scientific<<"||	"<< histogram1[hour];
		std::fill_n(std::ostream_iterator<std::string>(std::cout), 11, " ");
		std::cout<<(((histogram1[hour])/maxcapacity)*100.0);
		std::fill_n(std::ostream_iterator<std::string>(std::cout), 11, " ");
		std::cout<<histogram2[hour]<<std::endl;
	}
	std::fill_n(std::ostream_iterator<std::string>(std::cout), histogramsize+80, "#");
	std::cout<<std::endl;
	/* ################### END OF HISTOGRAM PRINTING ##########################################*/
	std::cout<<"Simulation ready. See the details of all roads in the outputfile."<<std::endl;
	//std::cout << "The number of cars that entered the roads from buildings: " << BuildingExitCrossroad::carsLeftHome << '\n';

}

#include "./include/Navigator.hpp"

#include <algorithm>
#include <vector>
#include <limits>
#include <iostream>
#include <math.h>
#include <functional>
#include <queue>

Navigator::Navigator(std::vector<RoadLineClass*> roads, std::vector<CrossroadClass*> crossroads):roads_(roads), crossroads_(crossroads){ }


/*A PRIVATE HELPER FUNCTION: Find the possible successors of given state, that is, the allowed (on-route) locations
that are one step away from given location.
Return the location with corresponding direction*/

std::vector<std::pair<CrossroadClass*,RoadLineClass*>> Navigator::successors(CrossroadClass* crossroad){
    std::vector<std::pair<CrossroadClass*,RoadLineClass*>> result;
    for (auto road : roads_){
        if(road->GetStart()==crossroad){
            result.push_back(std::make_pair(road->GetEnd(),road));
        }
    }
    return result;
}


std::vector<RoadLineClass*> Navigator::MakeRoute(CrossroadClass* start, CrossroadClass* finish) {
    //std::cout<<"Calling makeroute for navigator to go from: "<<start<< " to " <<finish <<std::endl;

    /*Init returnvector*/
    std::vector<RoadLineClass*> actions;

    /*Check whather start and finish differ, for debugging purposes*/
    /*if(start==finish){
        std::cout<<"start is equal to finish"<<std::endl;
        return actions;
    }*/
    /*A map to keep up with predecessors of each expanded state and the action that took us there*/
    std::map<CrossroadClass*,std::pair<RoadLineClass*,CrossroadClass*>> predecessors;

    /*A map to keep up with the length of the shortest route found to given location (so far)*/
    std::map<CrossroadClass*,double> pathlength;

    /*A priority queue to guide the search. Priority of each entry (search node) is the estimated
    distance to finish: path travelled so far plus euclidean distance to finish*/
    std::priority_queue<std::pair<double,CrossroadClass*>> Q;

    /*Variable to keep up with the best path length found*/
    double bestpath_length = std::numeric_limits<double>::max();

// ##################################### Begin search #####################################

    //Put start state in queue
    Q.push(std::make_pair(0.0,start));

    //and in pathlength- and predecessors-maps
    pathlength[start] = 0.0;
    predecessors[start] = std::make_pair(nullptr,nullptr);

    //While the queue is non-empty do:
    while (not Q.empty()){
        // Take out the search node with the highest priority = lowest estimated distance
        std::pair<double,CrossroadClass*> currpair = Q.top();
        Q.pop();
        CrossroadClass* curr = currpair.second;
        double est_dist = currpair.first;
        // Only if the estimated distance (lower bound) is shorter than the current best
        // path to goal state do:
        if (est_dist < bestpath_length){
            // go through all the possible successor-locations
            for (auto [succ,act] : successors(curr)){
                // if the location has not yet been expanded, or this new path is shorter
                // than the one found previously
                bool condition1 = (not pathlength.count(succ));
                bool condition2 = ((pathlength[curr]+ act->GetSize()*5) < pathlength[succ]); //roadsize times 5 to mach with the coordinates
                if ((condition1 || condition2)){
                    // update pathlength and predecessors
                    pathlength[succ]=pathlength[curr]+act->GetSize()*5; //roadsize times 5 to mach with the coordinates
                    predecessors[succ] = std::make_pair(act,curr);
                    // if the location is not a goal location, add it in queue
                    if (not (succ==finish)){
                        Q.push(std::make_pair((1/(pathlength[succ] + sqrt(1.0*pow((succ->getX()-finish->getX()),2)+1.0*pow((succ->getY()-finish->getY()),2)))),succ));
                    }
                    // and if it is a goal location, see if it's better than the previous
                    // best and update when needed
                    else if (pathlength[succ]<bestpath_length){
                        bestpath_length = pathlength[succ];
                    }
                }
            }
        }
    }

    // Follow the predecessors to reconstruct the solution

    // Start from the goal
    CrossroadClass* currstate = finish;

    // Move backwards until reaching start-state
    while (currstate != start && currstate != nullptr){
        std::pair<RoadLineClass*,CrossroadClass*> predecessor = predecessors[currstate];
        // collect actions
        actions.insert(actions.begin(),predecessor.first);
        currstate = predecessor.second;
    }

    /*Print path, for debugging purposes*/

    // std::cout << "PATH:" << std::endl;

    // for (RoadLineClass* action : actions){
    //     std::cout << "----ROAD START------" << std::endl;
    //     std::cout << "Start crossroad:" << action->GetStart() << std::endl;
    //     std::cout << "End crossroad:" << action->GetEnd()<< std::endl;
    //     //std::cout << "Road:" << action<< std::endl;
    //     std::cout << "----ROAD END------" << std::endl;
    // }
    return actions;
}

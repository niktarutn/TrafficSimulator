#ifndef NAVIGATOR_HPP
#define NAVIGATOR_HPP

#include <vector>

#include "roadlineclass.hpp"

/* 
* Navigator2 class. Takes a map to be constructed.
* Has a method MakeRoute which creates a route from start crossroad to end crossroad.
* Contact info - Emma
*/

class Navigator{
    public:
        Navigator(std::vector<RoadLineClass*> roads_,std::vector<CrossroadClass*> crossroads_);
        
        std::vector<RoadLineClass*>  MakeRoute(CrossroadClass* start, CrossroadClass* finish);
    private:
    std::vector<RoadLineClass*> roads_;
    std::vector<CrossroadClass*> crossroads_;

    
    // # Find the possible successors of given state, that is, the allowed (on-route) locations 
    // # that are one step away from given location.
    // # Return the location with corresponding direction
    std::vector<std::pair<CrossroadClass*,RoadLineClass*>> successors(CrossroadClass* crossroad);

};

#endif

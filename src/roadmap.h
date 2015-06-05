#ifndef _ROADMAP_H_
#define _ROADMAP_H_

#include "standard.h"
#include <fstream>
#include <sstream>

namespace Roadmap{
    
    void init(const char *file);
    void buildMap();
    bool isShortestPath(StationType src, StationType dst, int dis);
    
    extern Distance station_map[NUM_STATION][NUM_STATION];
}

#endif

#ifndef _ROADMAP_H_
#define _ROADMAP_H_

#include "standard.h"
#include <fstream>
#include <sstream>

namespace Roadmap{
    
    int convert(String s_name);
    void init(const char *file);
    void buildMap();
    
    extern String name[];
    extern String line; 
    extern String start;
    extern String destination;
    
    extern Distance dis;
    extern Distance station_map[12][12];
}

#endif

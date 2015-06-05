#include "roadmap.h"

const int INF = 0x7fffffff;

Distance Roadmap::station_map[NUM_STATION][NUM_STATION];

void Roadmap::init(const char *file) {
    for(int i = 0; i < NUM_STATION; i++){
        for(int j = 0; j < NUM_STATION; j++)
            station_map[i][j] = INF;
        station_map[i][i] = 0;
    }

    String line;
    String start;
    String destination;
    Distance dis;

    std::ifstream fin(file, std::ios::in);

    while (std::getline(fin, line) != NULL) {
        std::stringstream ss(line);
        ss >> start >> destination >> dis;

        StationType s = toStationType(start);
        StationType d = toStationType(destination);

        station_map[s][d] = station_map[d][s] = dis;
    }

    fin.close();
}

void Roadmap::buildMap() {
    for (int k = 0; k < NUM_STATION; k++)
        for (int i = 0; i < NUM_STATION; i++)
            for (int j = 0; j < NUM_STATION; j++)
                if(station_map[i][k] != INF && station_map[k][j] != INF)
                    station_map[i][j] = std::min(station_map[i][j], station_map[i][k] + station_map[k][j]);
}

bool Roadmap::isShortestPath(StationType src, StationType dst, int dis){
    return (dis <= station_map[src][dst]);
}

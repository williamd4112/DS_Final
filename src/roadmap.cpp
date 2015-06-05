#include "roadmap.h"

String Roadmap::name[] {
    "Danshui", 
    "Hongshulin", 
    "Beitou", 
    "Shilin", 
    "Zhongshan", 
    "Xinpu",
    "Ximen", 
    "Liuzhangli", 
    "Muzha", 
    "Guting", 
    "Gongguan", 
    "Jingmei"
};

String Roadmap::line; 
String Roadmap::start; 
String Roadmap::destination;
Distance Roadmap::dis;
Distance Roadmap::station_map[12][12];

int Roadmap::convert(String s_name) {
    for(int i = 0; i < 12 ; i++) {
        if(s_name == name[i]) return i;
    }
}

void Roadmap::init(const char *file) {
    ifstream fin(file, ios::in);
    while(getline(fin, line) != NULL){
        stringstream ss(line);
        ss >> start >> destination >> dis;
        int s = convert(start), d = convert(destination);
        station_map[s][d] = station_map[d][s] = distance;
    }
    fin.close();
}
void Roadmap::buildMap() {
    for(int k = 0; k < 12 ; k++)
        for(int i = 0; i < 12 ; i++)
            for(int j = 0; j <12 ; j++)
                 station_map[i][j] = min(station_map[i][j], station_map[i][k] + station_map[k][j]);
}

/*
	Functions:
	• NewBike
	• SearchBike
	• JunkBikePtr
	• TransBikePtr
	• RentBikePtr
	• Returns
	• Inquire
	• StationReport
	• UbikeReport
	• NetSearch
*/

#include "standard.h"
#include "bike.h"
#include "station.h"

BikePtr newBike(LicenseType license, Mileage Mile, BikeType bikeType, StationType station);
BikePtr searchBike(LicenseType license);
int junkBikePtr(BikePtr bike);
void transBikePtr(StationType station, BikePtr bike);
void rentBikePtr(StationType station, BikePtr bike);
int returns(StationType station, BikePtr bike, Mileage returnMile);
void inquire(LicenseType license);
void stationReport(StationType station);
void ubikeReport();
void netSearch(StationType station);
void hashReport();

void buildMap();

// Station graph
Distance road_map[NUM_STATION][NUM_STATION];

int main(int argc, char *argv[]){

	return 0;
}
#include "station.h"

Station::Station(StationType type):
	stationType(type),
	net(0) {
	std::fill(netType, netType + NUM_TYPE_OF_BIKE, 0);
}

Station::~Station() {

}

void Station::add(BikePtr bikeptr) {
	if (bikeptr == NULL)
		throw NullpointerException();
	bikeheaps[bikeptr->bikeType].insert(bikeptr);
}

void Station::rent(BikeType type) {
	// Find a free bike from heap
	// All bikes in the bikesheap would all be guranteed to be FREE
	if (bikeheaps[type].empty())
		throw NofreeBikeException();

	// Pop from bikes heap
	BikePtr freeBikePtr = bikeheaps[type].top();
	bikeheaps[type].pop();

	// Rent the bike
	freeBikePtr->rent();

	// Insert into rentheap
	rentheap.insert(freeBikePtr);
}

void Station::remove(BikePtr bikeptr) {
	if (bikeptr == NULL)
		throw NullpointerException();
	else if (bikeptr->status == RENTED)
		throw BikeonRented(bikeptr->license);
	bikeheaps[bikeptr->bikeType].deletes(bikeptr);
}

void Station::returns(BikePtr bikeptr, Mileage returnMile) {
	if (bikeptr == NULL)
		throw NullpointerException();

	// Delete from rent heap
	rentheap.deletes(bikeptr);

	// Returns the bike, call bike's return function
	bikeptr->returns(returnMile);

	// Re-add to the appropriate heap
	bikeheaps[bikeptr->bikeType].insert(bikeptr);
}

void Station::charge(BikeType bikeType, int profit) {
	netType[bikeType] += profit;
	net += profit;
}

void Station::report() {
	std::cout << std::setw(30) << stationtypeToStr(stationType) << std::endl;
	std::cout << std::setw(30) << "Free Bikes" << std::endl;
	print_fields(std::vector<String>(STATION_REPORT_FIELDS, STATION_REPORT_FIELDS + 4), 15);
	std::cout << SEP << std::endl;

	int subtotal = 0;
	for (int i = 0; i < NUM_TYPE_OF_BIKE; i++) {
		BikeHeap& heap = bikeheaps[i];
		for (BikeHeap::Iterator it = heap.begin(); it != heap.end(); ++it) {
			std::cout << std::setw(15) << (*it)->license
			          << std::setw(15) << (*it)->mile
			          << std::setw(15) << biketypeToStr((*it)->bikeType) << std::endl;
			subtotal++;
		}
	}

	std::cout << SEP << std::endl;
	std::cout << std::setw(60) << subtotal << std::endl << std::endl;

	subtotal = 0;
	std::cout << std::setw(30) << "Rented Bikes" << std::endl;
	print_fields(std::vector<String>(STATION_REPORT_FIELDS, STATION_REPORT_FIELDS + 4), 15);
	std::cout << SEP << std::endl;
	for (BikeHeap::Iterator it = rentheap.begin(); it != rentheap.end(); ++it) {
		std::cout << std::setw(15) << (*it)->license
		          << std::setw(15) << (*it)->mile
		          << std::setw(15) << biketypeToStr((*it)->bikeType) << std::endl;
		subtotal++;
	}
	std::cout << SEP << std::endl;
	std::cout << std::setw(60) << subtotal << std::endl << std::endl;

	PRINT_FIELD(UBIKE_REPORT_TOTAL_FIELDS, 5)
	std::cout << SEP << std::endl;

	std::vector<int> metrics = getMetrics();
	for (int i = 0; i < 5; i++)
		std::cout << std::setw(12) << metrics[i];
	std::cout << std::endl;
	std::cout << SEP << std::endl;
	std::cout << std::endl;
}

void Station::report_net() {
	std::cout << stationtypeToStr(stationType) << std::endl;
	std::cout << QUATER_SEP << std::endl;
	for (int i = 0; i < NUM_TYPE_OF_BIKE; i++)
		std::cout << biketypeToStr(BIKE_TYPES[i]) << " " << netType[i] << std::endl;
	std::cout << QUATER_SEP << std::endl;
	std::cout << "Total " << net << std::endl << std::endl;
}

std::vector<int> Station::getMetrics() {
	std::vector<int> metrics;
	metrics.push_back(net);

	// Free bikes
	for (int i = 0; i < NUM_TYPE_OF_BIKE; i++)
		metrics.push_back(bikeheaps[i].size());

	// Rented Bikes
	for (BikeHeap::Iterator it = rentheap.begin(); it != rentheap.end(); ++it)
		metrics[(*it)->getBikeType() + 1]++;

	return metrics;
}

std::list<BikePtr> Station::getFreeBikesPtr() {
	std::list<BikePtr> logs;
	for (int i = 0; i < NUM_TYPE_OF_BIKE; i++) 
		for (BikeHeap::Iterator it = bikeheaps[i].begin(); it != bikeheaps[i].end(); ++it) 
				logs.push_back(*it);
	return logs;
}

std::list<BikePtr> Station::getRentBikesPtr() {
	std::list<BikePtr> logs;
	for (BikeHeap::Iterator it = rentheap.begin(); it != rentheap.end(); ++it)
		logs.push_back(*it);
	return logs;
}

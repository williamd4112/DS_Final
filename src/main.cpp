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
#include "bikebase.h"
#include "station.h"
#include "roadmap.h"

typedef void (*instr_func)(std::vector<String>& args);
typedef struct instr_func_record {
	String op;
	instr_func func;
}instr_func_record;

void init();
void load_instruction(const char *filename);
std::vector<String> tokenize(String line);
void msg_licensenotfound(LicenseType license);
void msg_bikeonrented(LicenseType license);
void msg_nofreebike();
void msg_indexoutofbound(int i);

// Format: NewBike [BikeType] [LicenseType] [Mileage] [StationType]
void i_newBike(std::vector<String>& args);

// Format: JunkIt [LicenseType]
void i_junkBikePtr(std::vector<String>& args);

// Format: Trans [LicenseType]
void i_transBikePtr(std::vector<String>& args);

// Format: Rent [StationType] [BikeType]
void i_rentBikePtr(std::vector<String>& args);

// Format: Returns [StationType] [LicenseType] [ReturnMiles]
void i_returns(std::vector<String>& args);

// Format: Inquire [LicenseType]
void i_inquire(std::vector<String>& args);

// Format: StationReport [StationType]
void i_stationReport(std::vector<String>& args);

// Format: UbikeReport
void i_ubikeReport(std::vector<String>& args);

// Format: NetSearch [StationType]
void i_netSearch(std::vector<String>& args);

// Format: HashReport
void i_hashReport(std::vector<String>& args);

// Format: Junk [LicenseType]
void junkBikePtr(LicenseType license);

instr_func_record INSTR_FUNC_TABLE[] = {
	{"NewBike", i_newBike},
	{"Inquire", i_inquire},
	{"JunkIt", i_junkBikePtr},
	{"Trans", i_transBikePtr},
	{"Rent", i_rentBikePtr},
	{"Returns", i_returns},
	{"StationReport", i_stationReport},
	{"NetSearch", i_netSearch},
	{"HashReport", i_hashReport},
	{"UbikeReport", i_ubikeReport},
	{"", NULL}
};

Bikebase bikebase(MAX_BIKEBASE_SIZE);
std::vector<Station> stations;

void init(){
	for(int i = 0; i < NUM_STATION; i++)
		stations.push_back(Station(STATION_TYPES[i]));
}

std::vector<String> tokenize(String line){
	Stringstream ss(line);
	std::vector<String> tokens;
	String token;
	while(ss >> token)
		tokens.push_back(token);
	return tokens;
}

void msg_licensenotfound(LicenseType license){
	std::cout << "Bike " << license << " does not belong to our company." << std::endl;
}

void msg_bikeonrented(LicenseType license){
	std::cout << "Bike " << license << " is now being rented." << std::endl;
}

void msg_indexoutofbound(int i){
	std::cerr << "Index out of bound: " << i << std::endl;
}

void msg_nofreebike(){
	std::cout << "No free bike is available." << std::endl;
}

void i_newBike(std::vector<String>& args){
	
	// Parsing arguments
	if(args.size() < 5)
		throw std::invalid_argument("Number of arguments is too few");
		
	BikeType bikeType = toBikeType(args[1]);
	LicenseType license(args[2].c_str());
	Mileage mile(std::stoi(args[3]));
	StationType station = toStationType(args[4]);
	
	// Create a bike in the bikebase
	BikePtr bikeptr = bikebase.add(license, mile, bikeType, station);
	
	// Assign the bike to station
	stations[station].add(bikeptr);
	
	std::cout << "New bike is received by Station " << stationtypeToStr(station) << "." << std::endl;
	
}

void i_inquire(std::vector<String>& args){
	// Parsing arguments
	if(args.size() < 2)
		throw std::invalid_argument("inquire(): Number of arguments is too few");

	try{
		LicenseType inquire_license(args[1].c_str());
	
		// Lookup from bikebase
		BikePtr bikeptr = bikebase[inquire_license];
		print_fields(std::vector<String>(UBIKE_REPORT_FREEBIKES_FIELDS, UBIKE_REPORT_FREEBIKES_FIELDS + 4), 15);
		std::cout << SEP << std::endl;
		std::cout << bikeptr->getLog(15) << std::endl << std::endl;
	}
	catch(LicenseNotFoundException e){
		msg_licensenotfound(e.license);
	}
	catch(BikeonRented e){
		msg_bikeonrented(e.license);
	}
	catch(IndexOutofBoundException e){
		msg_indexoutofbound(e.i);
	}
}

void i_transBikePtr(std::vector<String>& args){
	if(args.size() < 3)
		throw std::invalid_argument("Number of arguments is too few");
	
	try{
		StationType new_station = toStationType(args[1]);
		LicenseType trans_license(args[2].c_str());
		
		// Get Bikeptr from bikebase
		BikePtr bikeptr = bikebase[trans_license];
		
		// Get origin station
		StationType ori_station = bikeptr->getStationType();
		
		// Trans the bike
		bikeptr->trans(new_station);
		
		// Remove the bike from origin station
		stations[ori_station].remove(bikeptr);
		
		// Add the bike to the new station
		stations[new_station].add(bikeptr);
		
		std::cout << "Bike " << trans_license << " is transferred to " << stationtypeToStr(new_station) << "." << std::endl;
		
	}
	catch(LicenseNotFoundException e){
		msg_licensenotfound(e.license);
	}
	catch(BikeonRented e){
		msg_bikeonrented(e.license);
	}
	catch(IndexOutofBoundException e){
		msg_indexoutofbound(e.i);
	}
	
}

void i_rentBikePtr(std::vector<String>& args){
	if(args.size() < 3)
		throw std::invalid_argument("Number of arguments is too few");
	
	try{
		StationType station = toStationType(args[1]);
		BikeType bikeType = toBikeType(args[2]);
		
		// Rent from the station
		stations[station].rent(bikeType);
		
		std::cout << "A bike is rented from " << stationtypeToStr(station) << "." << std::endl;
	}
	catch(NofreeBikeException e){
		msg_nofreebike();
	}
}

void i_junkBikePtr(std::vector<String>& args){
	// Parsing arguments
	if(args.size() < 2)
		throw std::invalid_argument("Number of arguments is too few");
		
	try{
		LicenseType junk_license = LicenseType(args[1].c_str());
		
		// Get the bikeptr from bikebase (bikebase's get function will gurantee non-null pointer return)
		BikePtr junk_ptr = bikebase[junk_license];

		// Record the station before delete
		StationType station = junk_ptr->getStationType();
		
		// Remove from station
		stations[station].remove(junk_ptr);

		// Remove from bikebase (NOTE: this operation will free this bike's memory)
		bikebase.remove(junk_ptr);
		
		std::cout << "Bike " << junk_license << " is deleted from " << stationtypeToStr(station) << "." << std::endl;
	}
	catch(LicenseNotFoundException e){
		msg_licensenotfound(e.license);
	}
	catch(BikeonRented e){
		msg_bikeonrented(e.license);
	}
	catch(IndexOutofBoundException e){
		msg_indexoutofbound(e.i);
	}
}

void i_returns(std::vector<String>& args){
	// Parsing arguments
	if(args.size() < 4)
		throw std::invalid_argument("Number of arguments is too few");
	
	StationType return_station = toStationType(args[1]);
	LicenseType license(args[2].c_str());
	Mileage returnMile = std::stoi(args[3]);
		
	BikePtr bikeptr = bikebase[license];
	BikeType bikeType = bikeptr->getBikeType();
	Mileage ori_mile = bikeptr->getMile();
	StationType ori_station = bikeptr->getStationType();
		
	// Returns to the ori_station
	stations[ori_station].returns(bikeptr, returnMile);
		
	// Lookup the charge
	for(int i = 0; i < NUM_TYPE_OF_BIKE; i++){
		if(discount_table[i].biketype == bikeType){			
			// Charge the station
			Distance dis_diff = (returnMile - ori_mile);
			Cost rental_charge;
			if(Roadmap::isShortestPath(ori_station, return_station, dis_diff))
				rental_charge = dis_diff * discount_table[i].discount;
			else
				rental_charge = dis_diff * discount_table[i].original;

			stations[ori_station].charge(bikeType, rental_charge);
			std::cout << "Rental charge for this bike is " << rental_charge << "." << std::endl;
			break;
		}
	}
}

void i_stationReport(std::vector<String>& args){
	if(args.size() < 2)
		throw std::invalid_argument("Number of arguments is too few");
	
	StationType station = toStationType(args[1]);
	stations[station].report();
	
}

void i_netSearch(std::vector<String>& args){
	if(args.size() < 2)
		throw std::invalid_argument("Number of arguments is too few");
	StationType station = toStationType(args[1]);
	stations[station].report_net();
}

void i_hashReport(std::vector<String>& args){
	bikebase.report();
}

void i_ubikeReport(std::vector<String>& args){
	std::list<BikePtr> station_free_logs;
	for(int i = 0; i < NUM_STATION; i++){
		std::list<BikePtr> log = stations[i].getFreeBikesPtr();
		station_free_logs.insert(station_free_logs.end(), log.begin(), log.end());
	}

	std::list<BikePtr> station_rent_logs;
	for(int i = 0; i < NUM_STATION; i++){
		std::list<BikePtr> log = stations[i].getRentBikesPtr();
		station_rent_logs.insert(station_rent_logs.end(), log.begin(), log.end());
	}

   	std::cout << std::setw(30) << "Taipei U-bike" << std::endl;
	std::cout << std::setw(30) << "Free Bikes" << std::endl;
	print_fields(std::vector<String>(UBIKE_REPORT_FREEBIKES_FIELDS, UBIKE_REPORT_FREEBIKES_FIELDS + 5), 12);
	std::cout << SEP << std::endl;
	for(std::list<BikePtr>::iterator it = station_free_logs.begin(); it != station_free_logs.end(); it++)
		std::cout << (*it)->getLog(12) << std::endl;
	std::cout << SEP << std::endl;
	std::cout << std::setw(60) << station_free_logs.size() << std::endl << std::endl;
    
    std::cout << std::setw(30) << "Rented Bikes" << std::endl;
    print_fields(std::vector<String>(UBIKE_REPORT_FREEBIKES_FIELDS, UBIKE_REPORT_FREEBIKES_FIELDS + 5), 12);
    std::cout << SEP << std::endl;
    for(std::list<BikePtr>::iterator it = station_rent_logs.begin(); it != station_rent_logs.end(); it++)
		std::cout << std::setw(12) << (*it)->getLog(12) << std::endl;
	std::cout << SEP << std::endl;
	std::cout << std::setw(60) << station_rent_logs.size() << std::endl << std::endl;

	std::vector<int> metrics(5, 0);
	for(int i = 0; i < NUM_STATION; i++){
		std::vector<int> s = stations[i].getMetrics();
		for(int i = 0; i < s.size(); i++)
			metrics[i] += s[i];
	}
	
	print_fields(std::vector<String>(UBIKE_REPORT_TOTAL_FIELDS, UBIKE_REPORT_TOTAL_FIELDS + 5), 12);
	std::cout << SEP << std::endl;
	for(int i = 0; i < 5; i++)
		std::cout << std::setw(12) << metrics[i];
	std::cout << std::endl;
	std::cout << SEP << std::endl << std::endl;
}

void load_instruction(const char *filename){
	std::ifstream ifs;
  	ifs.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  	
  	String line;
  	try {
    	ifs.open (filename, std::ios::in);
    	
    	while (!ifs.eof()){ 
    		getline(ifs, line);
    		std::vector<String> args = tokenize(line);
    		if(args.size() < 1)
    			throw std::invalid_argument("Number of arguments is too few");
    		
    		for(int i = 0; INSTR_FUNC_TABLE[i].func != NULL; i++)
    			if(INSTR_FUNC_TABLE[i].op == args[0])
    				INSTR_FUNC_TABLE[i].func(args);
    	}
  	}
  	catch (std::ifstream::failure e) {
    	//std::cerr << "load_instruction(): load file error" << std::endl;
    	return;
  	}
  	catch (std::invalid_argument e) {
  		std::cerr << "load_instruction(): " << e.what() << std::endl;
  	}
  	catch(BikeTypeStringConversionException e){
  		std::cerr << "load_instruction(): " << e.what() << std::endl;
  	}
  	catch(StationTypeStringConversionException e){
  		std::cerr << "load_instruction(): " << e.what() << " cannot convert to StationType" << std::endl;
  	}
  	catch(NullpointerException e){
  		std::cerr << "load_instruction(): null pointer exception at " << line << std::endl;
  	}

  	ifs.close();
}

void showMap(){
	std::cout << std::setw(3) << " ";
	for(int i = 0; i < NUM_STATION; i++)
		std::cout << std::setw(3) << i;
	std::cout << std::endl;
	for(int i = 0; i < NUM_STATION; i++){
		std::cout << std::setw(3) << i;
		for(int j = 0; j < NUM_STATION; j++)
			std::cout << std::setw(3) << Roadmap::station_map[i][j];
		std::cout << std::endl;
	}
}

int main(int argc, char *argv[]){
	if(argc < 4){
		std::cout << "Usage: ./main.out [Instruction File] [Map File] [Output File] " << std::endl;
		return 0;
	}
	
	freopen(argv[3], "w", stdout);

	init();
	Roadmap::init(argv[2]);
	Roadmap::buildMap();
	load_instruction(argv[1]);

	return 0;
}


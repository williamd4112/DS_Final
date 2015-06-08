#include "standard.h"

String SEP = "============================================================";
String QUATER_SEP = "===============";

DiscountRecord discount_table[] = {
	{Electric, 30, 40},
	{Lady, 25, 30},
	{Road, 15, 20},
	{Hybrid, 20, 25}
};


StationType STATION_TYPES[] = {
	Danshui,
	Hongshulin, 
	Beitou,
	Shilin, 
	Zhongshan, 
	Xinpu,
	Ximen, 
	Liuzhangli, 
	Muzha,
	Guting, 
	Gongguan, 
	Jingmei
};

BikeType BIKE_TYPES[] = {
	Electric,
	Lady,
	Road,
	Hybrid
};

String station_table[] = {
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

String biketype_table[] = {
	"Electric",
	"Lady",
	"Road",
	"Hybrid"
};

BikeTypeRecord biketypeRecord_table[] = {
	{"Electric", Electric},
	{"Lady", Lady},
	{"Road", Road},
	{"Hybrid", Hybrid}
};

StationTypeRecord stationtypeRecord_table[] = {
	{"Danshui", Danshui},
	{"Hongshulin", Hongshulin} ,
	{"Beitou", Beitou},
	{"Shilin", Shilin}, 
	{"Zhongshan", Zhongshan}, 
	{"Xinpu", Xinpu},
	{"Ximen", Ximen}, 
	{"Liuzhangli", Liuzhangli}, 
	{"Muzha", Muzha},
	{"Guting", Guting}, 
	{"Gongguan", Gongguan}, 
	{"Jingmei", Jingmei}
};

String UBIKE_REPORT_FREEBIKES_FIELDS[] = {
    "License",
    "Mileage",
    "Class",
    "Station",
    "Total"
};

String UBIKE_REPORT_TOTAL_FIELDS[]{
    "Net",
    "Electric",
    "Lady",
    "Road",
    "Hybrid"
};

String STATION_REPORT_FIELDS[] = {
	"License",
    "Mileage",
    "Class",
    "SubTotal"
};

BikeType toBikeType(String bikeType_s){
	for(int i = 0; i < NUM_TYPE_OF_BIKE; i++)
		if(biketypeRecord_table[i].bikeType_s == bikeType_s)
			return biketypeRecord_table[i].bikeType_e;
	throw BikeTypeStringConversionException();
}

StationType toStationType(String stationType_s){
	for(int i = 0; i < NUM_STATION; i++)
		if(stationtypeRecord_table[i].stationType_s == stationType_s)
			return stationtypeRecord_table[i].stationType_e;
	throw StationTypeStringConversionException(stationType_s);
}

String biketypeToStr(BikeType biketype){
	if(biketype < 0 || biketype >= NUM_TYPE_OF_BIKE)
		throw IndexOutofBoundException(biketype);
	return biketype_table[biketype];
}

String stationtypeToStr(StationType stationtype){
	if(stationtype < 0 || stationtype >= NUM_STATION)
		throw IndexOutofBoundException(stationtype);
	return station_table[stationtype];
}

void print_fields(std::vector<String> fields, int width){
	for(int i = 0; i < fields.size(); i++)
		std::cout << std::setw(width) << fields[i];
	std::cout << std::endl;
}
#ifndef _STANDARD_H_
#define _STANDARD_H_

#define LICENSE_SIZE 5
#define NUM_STATION 12
#define NUM_TYPE_OF_BIKE 4
#define MAX_BIKEBASE_SIZE 256

#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <iterator>
#include <list>
#include <algorithm>
#include <ctype.h>
#include <sstream>
#include <cstring>
#include <iomanip>

#define PRINT_SEP for(int i = 0; i < 60; i++) std::cout << "="; std::cout << std::endl;
#define PRINT_FIELD(f, c) for(int i = 0; i < (c); i++) std::cout << std::setw(12) << (f)[i]; std::cout << std::endl;

enum StatusType {
	FREE, 
	RENTED
};

enum StationType{
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

enum BikeType{
	Electric,
	Lady,
	Road,
	Hybrid
};

typedef struct LicenseType {
	char license_number[LICENSE_SIZE + 1];
	
	LicenseType(const char *str){
		strncpy(license_number, str, LICENSE_SIZE);
		license_number[LICENSE_SIZE] = '\0'; 
	}
	
	LicenseType(const LicenseType& license){
		strncpy(license_number, license.license_number, LICENSE_SIZE);
		license_number[LICENSE_SIZE] = '\0';
	}
	
	int operator [](const int i){
		return isalpha(license_number[i]) ? (license_number[i] - 'A' + 10) : license_number[i] - '0';
	}
	
	bool operator ==(const LicenseType license){
		return strncmp(license_number, license.license_number, LICENSE_SIZE) == 0;
	}
	
	bool operator <(const LicenseType license){
		return strncmp(license_number, license.license_number, LICENSE_SIZE) < 0;
	}
	
	bool operator >(const LicenseType license){
		return strncmp(license_number, license.license_number, LICENSE_SIZE) > 0;
	}
	
	
	LicenseType operator =(const LicenseType& license){
		return LicenseType(license);
	}
	
	friend std::ostream& operator <<(std::ostream& os, const LicenseType license){
		os << license.license_number;
	}
}LicenseType;

typedef unsigned int Mileage;
typedef int Cost;
typedef int Distance;
typedef int Hashcode;

typedef std::string String;
typedef std::stringstream Stringstream;

typedef struct DiscountRecord{
	BikeType biketype;
	Cost discount;
	Cost original;
}DiscountRecord;

typedef struct BikeTypeRecord{
	String bikeType_s;
	BikeType bikeType_e;
}BikeTypeRecord;

typedef struct StationTypeRecord{
	String stationType_s;
	StationType stationType_e;
}StationTypeRecord;

struct IndexOutofBoundException: std::exception {
	
	const int i;
	
	IndexOutofBoundException(int i):
	i(i){
		
	}
	
	const char* what() const noexcept {
		return "IndexOutofBoundException";
	}
};

struct NullpointerException: std::exception {
	const char* what() const noexcept {
		return "NullpointerException";
	}
};

struct LicenseNotFoundException: std::exception {
	const LicenseType license;
	
	LicenseNotFoundException(const LicenseType license):
	license(LicenseType(license)){
		
	}
	
	const char* what() const noexcept {
		return license.license_number;
	}
};

struct EmptyContainerException: std::exception{
	const char* what() const noexcept {
		return "Empty Container";
	}
};

struct BikeonRented: std::exception {
	const LicenseType license;
	
	BikeonRented(const LicenseType license):
	license(LicenseType(license)){
		
	}
	
	const char* what() const noexcept {
		std::stringstream ss;
		ss << "Bike " << license << " is now being rented.";
		return ss.str().c_str();
	}
};

struct NofreeBikeException: std::exception {
	const char* what() const noexcept {
		return "No free bike is available.";
	}	
};

struct BikeTypeStringConversionException: std::exception {
	const char* what() const noexcept {
		return "toBikeType(): given string is not valid BikeType";
	}	
};

struct StationTypeStringConversionException: std::exception {
	
	const String str;
	
	StationTypeStringConversionException(String str):
	str(str){
		
	}
	
	const char* what() const noexcept {
		return str.c_str();
	}	
};


/*
	toBikeType(String bikeType_s):
	convert bikeType string to BikeType
	
	@throw BikeTypeStringConversionException: when passing string is not bike type
*/
BikeType toBikeType(String bikeType_s);

/*
	toBikeType(String bikeType_s):
	convert bikeType string to BikeType
	
	@throw StationTypeStringConversionException: when passing string is not station type
*/
StationType toStationType(String stationType_s);

/*
	biketypeToStr(BikeType biketype):
	convert biketype from enum to string
*/
String biketypeToStr(BikeType biketype);

/*
	stationtypeToStr(StationType stationtype):
	convert stationtype from enum to string
*/
String stationtypeToStr(StationType stationtype);

void print_fields(std::vector<String> fields, int width);

extern DiscountRecord discount_table[];
extern String station_table[];
extern String biketype_table[];

extern String SEP;
extern BikeType BIKE_TYPES[];
extern StationType STATION_TYPES[];
extern String UBIKE_REPORT_FREEBIKES_FIELDS[];
extern String UBIKE_REPORT_TOTAL_FIELDS[];
extern String STATION_REPORT_FIELDS[];

#endif
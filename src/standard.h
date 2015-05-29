#ifndef _STANDARD_H_
#define _STANDARD_H_

#define LICENSE_SIZE 5
#define NUM_STATION 12

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <list>
#include <algorithm>

enum StatusType {
	Free, 
	Rented
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

typedef unsigned int Mileage;
typedef int CursorType;
typedef int Cost;
typedef int Distance;
typedef int Hashcode;

typedef struct LicenseType {
	char license_number[LICENSE_SIZE + 1];
}LicenseType;

typedef struct DiscountRecord{
	BikeType biketype;
	Cost discount;
	Cost original;
}DiscountRecord;

typedef std::string String;

#endif
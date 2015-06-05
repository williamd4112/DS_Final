#include "bike.h"

Bike::Bike(LicenseType license, Mileage mile, BikeType bikeType, StationType station):
license(LicenseType(license)),
mile(mile),
bikeType(bikeType),
stationType(station),
status(FREE){
    
}

Bike::Bike(LicenseType license):
license(LicenseType(license)),
mile(0),
bikeType(Electric),
stationType(Danshui),
status(FREE){
    
}
	

Bike::~Bike(){
    
}

void Bike::trans(StationType station){
    if(status == RENTED)
        throw BikeonRented(license);
    stationType = station;
}

void Bike::rent(){
    status = RENTED;
}

void Bike::returns(Mileage returnMile){
    // Reset to free status
    status = FREE;
    
    // Update accumulated miles
    mile = returnMile;
}

void Bike::setCursor(BikeHeapCursor _cursor){
    cursor = _cursor;
}

LicenseType Bike::getLicense() const{
    return license;
}

Mileage Bike::getMile() const{
    return mile;
}

BikeType Bike::getBikeType() const{
    return bikeType;
}

StationType Bike::getStationType() const{
    return stationType;
}

StatusType Bike::getStatus() const{
    return status;
}

String Bike::getLog(int width){
    std::stringstream ss;
    ss << std::setw(width) << getLicense();
    ss << std::setw(width) << getMile();
    ss << std::setw(width) << biketypeToStr(getBikeType());
    ss << std::setw(width) << stationtypeToStr(getStationType());
    return ss.str();
}

bool Bike::operator ==(const Bike b){
    return license == b.license;
}

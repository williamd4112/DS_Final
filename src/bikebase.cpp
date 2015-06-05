#include "bikebase.h"

Bikebase::Bikebase(size_t table_size):
hash_table(std::vector<HNode>( table_size, HNode() ) ),
table_size(table_size),
bike_num(0){
}

Bikebase::~Bikebase(){

}

BikePtr Bikebase::get(LicenseType license){
    HNode& hnode = hash_table[toHash(license)];
    for(HNode::iterator it = hnode.begin(); it != hnode.end(); it++){
        if(it->license == license){
            Bike& ref = *it;
            return &ref;
        }
    }
    
    throw LicenseNotFoundException(license);
}

void Bikebase::remove(BikePtr bikeptr){
    if(bikeptr == NULL)
        throw NullpointerException();
    hash_table[toHash(bikeptr->license)].remove(*bikeptr);
}

BikePtr Bikebase::add(LicenseType license, Mileage mile, BikeType bikeType, StationType station){
    Hashcode hashcode = toHash(license);
    hash_table[hashcode].push_back(Bike(license, mile, bikeType, station));
    
    return &hash_table[hashcode].back();
}

Hashcode Bikebase::toHash(LicenseType license){
	Hashcode hashcode = license[0];
	for(int i = 1; i < LICENSE_SIZE; i++)
	    hashcode = hashcode * 31 + license[i];
	return (hashcode >> 10) & 0xff;
}

std::vector<HNode>& Bikebase::getHashtable(){
    return hash_table;
}

BikePtr Bikebase::operator [](const LicenseType license){
    return get(license);
}
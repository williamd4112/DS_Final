#include "bikebase.h"

Bikebase::Bikebase(size_t table_size):
    hash_table(std::vector<HNode>( table_size, HNode() ) ),
    table_size(table_size),
    bike_num(0) {
}

Bikebase::~Bikebase() {

}

BikePtr Bikebase::get(LicenseType license) {
    HNode& hnode = hash_table[toHash(license)];
    for (HNode::iterator it = hnode.begin(); it != hnode.end(); it++) {
        if (*it == NULL)
            throw NullpointerException();
        if ((*it)->license == license)
            return *it;
    }

    throw LicenseNotFoundException(license);
}

void Bikebase::remove(BikePtr bikeptr) {
    if (bikeptr == NULL)
        throw NullpointerException();
    hash_table[toHash(bikeptr->license)].remove(bikeptr);
}

BikePtr Bikebase::add(LicenseType license, Mileage mile, BikeType bikeType, StationType station) {
    Hashcode hashcode = toHash(license);
    BikePtr bikeptr = new Bike(license, mile, bikeType, station);
    hash_table[hashcode].push_back(bikeptr);

    return bikeptr;
}

Hashcode Bikebase::toHash(LicenseType license) {
    Hashcode hashcode = license[0];
    for (int i = 1; i < LICENSE_SIZE; i++)
        hashcode = hashcode * 31 + license[i];
    return (hashcode >> 10) & 0xff;
}

BikePtr Bikebase::operator [](const LicenseType license) {
    return get(license);
}

void Bikebase::report() {
    std::cout << "Hash Table" << std::endl;
    for (int i = 0; i < hash_table.size(); i++) {
        if (hash_table[i].size() < 1)
            continue;

        bool first = true;
        HNode& hnode = hash_table[i];
        for (HNode::iterator it = hnode.begin(); it != hnode.end(); it++)
            if (!first)
                std::cout  << "->" << (*it)->getLicense();
            else {
                first = false;
                std::cout  << i << " " << (*it)->getLicense();
            }
        std::cout  << std::endl;
    }
}
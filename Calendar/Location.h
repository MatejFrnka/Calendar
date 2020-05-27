/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 27.05.2020
 */

#ifndef CALENDAR_LOCATION_H
#define CALENDAR_LOCATION_H

#include "string"

struct Location {
    Location(std::string address_) : address(address_) {};
    std::string address;
};


#endif //CALENDAR_LOCATION_H

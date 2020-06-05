/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 05.06.2020
 */

#ifndef CALENDAR_UNEXPECTEDENDOFINPUTEXCEPTION_H
#define CALENDAR_UNEXPECTEDENDOFINPUTEXCEPTION_H

#include <exception>

class UnexpectedEndOfInputException : std::exception {
    virtual const char *what() const throw() {
        return "Input ended unexpectedly";
    }
};

#endif //CALENDAR_UNEXPECTEDENDOFINPUTEXCEPTION_H

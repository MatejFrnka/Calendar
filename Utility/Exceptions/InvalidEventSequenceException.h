/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 02.06.2020
 */

#ifndef CALENDAR_INVALIDEVENTSEQUENCEEXCEPTION_H
#define CALENDAR_INVALIDEVENTSEQUENCEEXCEPTION_H

#include <exception>

/**
 * Used when trying to generate event from recurring event but the generated event does not mach recurring pattern of the recurring event
 */
class InvalidEventSequenceException : std::exception {
    virtual const char *what() const throw() {
        return "Error while loading event - invalid input";
    }
};

#endif //CALENDAR_INVALIDEVENTSEQUENCEEXCEPTION_H

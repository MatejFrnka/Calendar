/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 02.05.2020
 */

#pragma once
#include <exception>

/**
 * Used when trying to generate event from recurring event but the generated event does not mach recurring pattern of the recurring event
 */
class EventNotInRecurringEventException : std::exception {
    virtual const char *what() const throw() {
        return "Event is not in recurring exception";
    }
};

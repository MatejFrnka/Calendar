/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 02.06.2020
 */

#pragma once
#include <exception>

/**
 * Used when trying to generate event from recurring event but the generated event does not mach recurring pattern of the recurring event
 */
class InvalidEventSequenceException : std::exception {
    virtual const char *what() const throw() {
        return "Error while loading event - invalid input";
    }
};

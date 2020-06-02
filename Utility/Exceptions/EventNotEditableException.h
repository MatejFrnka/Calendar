/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 01.05.2020
 */

#ifndef CALENDAR_UTILITY_EXCEPTIONS_EVENT_NOT_EDITABLE
#define CALENDAR_UTILITY_EXCEPTIONS_EVENT_NOT_EDITABLE

#include <exception>

/**
 * Used when trying to edit attribute of event that can not be edited
 */
class EventNotEditableException : std::exception {
    virtual const char *what() const throw() {
        return "Event is not editable";
    }
};


#endif
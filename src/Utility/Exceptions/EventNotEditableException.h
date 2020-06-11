/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 01.05.2020
 */

#pragma once
#include <exception>

/**
 * Used when trying to edit attribute of event that can not be edited
 */
class EventNotEditableException : std::exception {
    virtual const char *what() const throw() {
        return "Event is not editable";
    }
};



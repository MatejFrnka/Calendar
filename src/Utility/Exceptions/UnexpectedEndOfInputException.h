/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 05.06.2020
 */

#pragma once
#include <exception>

class UnexpectedEndOfInputException : std::exception {
    virtual const char *what() const throw() {
        return "Input ended unexpectedly";
    }
};

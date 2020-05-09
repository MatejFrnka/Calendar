/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 06.05.2020
 */

#ifndef CALENDAR_APP_INTERFACE
#define CALENDAR_APP_INTERFACE

#include "string"

class Interface {
    void start();

    template<typename T>
    T getInput(const std::string &dialog);

    bool showDialog(const std::string &message);
};


#endif
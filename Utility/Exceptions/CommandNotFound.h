/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 22.05.2020
 */

#ifndef CALENDAR_COMMANDNOTFOUND_H
#define CALENDAR_COMMANDNOTFOUND_H


#include <exception>
#include <string>
#include <utility>

class CommandNotFound : public std::exception {
public:
    explicit CommandNotFound(const std::string& commandName) {
        message = "Command " + commandName + " was not found";
    }

    virtual const char *what() const throw() {
        return message.c_str();
    }

private:
    std::string message;
};


#endif //CALENDAR_COMMANDNOTFOUND_H

/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 22.05.2020
 */

#ifndef CALENDAR_COMMANDNOTFOUNDEXCEPTION_H
#define CALENDAR_COMMANDNOTFOUNDEXCEPTION_H


#include <exception>
#include <string>
#include <utility>

class CommandNotFoundException : public std::exception {
public:
    explicit CommandNotFoundException(const std::string& commandName) {
        message = "Command " + commandName + " was not found";
    }

    virtual const char *what() const throw() {
        return message.c_str();
    }

private:
    std::string message;
};


#endif //CALENDAR_COMMANDNOTFOUNDEXCEPTION_H

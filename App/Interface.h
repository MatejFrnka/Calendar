/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 06.05.2020
 */

#ifndef CALENDAR_APP_INTERFACE
#define CALENDAR_APP_INTERFACE

#include "string"
#include "Commands/Command.h"
#include "Commands/HelpCommand.h"
#include "Commands/CreateCommand.h"
#include <iostream>
#include <vector>
#include <memory>

class Interface {
public:
    Interface(std::istream &in, std::ostream &out);

    void start();

private:
    std::istream &in;
    std::ostream &out;

    Command::outcome executeAction(const std::string &commandName, const std::vector<std::unique_ptr<Command>>& commands);

    template<typename T>
    T getInput(const std::string &dialog);

    bool showDialog(const std::string &message);

    std::vector<std::unique_ptr<Command>> homeCommands;
};

#endif
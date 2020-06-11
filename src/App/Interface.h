/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 06.05.2020
 */

#pragma once
#include "string"
#include "Commands/Command.h"
#include "Commands/HelpCommand.h"
#include "Commands/CreateCommand.h"
#include "Commands/Selected/DeleteCommand.h"
#include "../Utility/InputUtility.h"
#include "../Calendar/EventManager.h"
#include "../Draw/DrawManager.h"
#include <iostream>
#include <vector>
#include <memory>

class Interface {
public:
    Interface(std::istream &in_, std::ostream &out_, EventManager &eventManager_);

    Interface(const Interface &) = delete;

    void start();

private:
    std::istream &in;
    std::ostream &out;
    InputUtility inputUtility;

    std::vector<std::shared_ptr<Command>> executeAction(const std::string &commandName, const std::vector<std::shared_ptr<Command>> &commands);

    std::vector<std::shared_ptr<Command>> executeAction(std::queue<std::string> &parameters, const std::vector<std::shared_ptr<Command>> &commands);

    std::vector<std::shared_ptr<Command>> homeCommands;
    EventManager &eventManager;

    DrawManager drawManager;
};

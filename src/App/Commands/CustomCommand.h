/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 10.05.2020
 */

#pragma once
#include <functional>
#include <utility>
#include "Command.h"

class CustomCommand : public Command {
public:
    CustomCommand(std::string name, std::string description, InputUtility &inputUtility_, std::function<std::vector<std::shared_ptr<Command>>(std::queue<std::string> &, CustomCommand &self)> function)
            : Command(move(name), move(description), inputUtility_), fn(move(function)) {}

    CustomCommand(std::string name, std::string description, InputUtility &inputUtility_, std::function<std::vector<std::shared_ptr<Command>>(std::queue<std::string> &, CustomCommand &self)> function,
                  std::vector<std::shared_ptr<Command>> commands_)
            : Command(move(name), move(description), inputUtility_), fn(move(function)) {
        commands = std::move(commands_);
    }

    std::vector<std::shared_ptr<Command>> executeAction(std::queue<std::string> &parameters) override {
        return fn(parameters, *this);
    };
private:
    const std::function<std::vector<std::shared_ptr<Command>>(std::queue<std::string> &, CustomCommand &self)> fn;
};


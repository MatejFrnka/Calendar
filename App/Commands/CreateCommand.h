/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 09.05.2020
 */

#ifndef CALENDAR_APP_COMMANDS_CREATE_COMMAND
#define CALENDAR_APP_COMMANDS_CREATE_COMMAND

#include <utility>
#include <vector>
#include "Command.h"
#include "CustomCommand.h"
#include "../../Calendar/EventManager.h"

class CreateCommand : public Command {
public:
    CreateCommand(std::ostream &out, EventManager &eventManager) : Command("create", "Used to create a new event", out) {
        //TODO:ADD PROPER DESCRIPTION
        //
        CustomCommand single("single", "Single event happens only once.", out, [&eventManager](const std::vector<std::string> &params, CustomCommand &self) {
            eventManager.addEvent(SingleEvent::getInstance("test", 0, 50));
            self.out << "creating single event... -  ui not implemented yet";
            return std::vector<std::shared_ptr<Command>>();
        });
        commands.push_back(make_shared<CustomCommand>(single));

        CustomCommand recurring("recurring", "todo todo", out, [](const std::vector<std::string> &params, CustomCommand &self) {
            std::vector<std::shared_ptr<Command>> result;
            self.out << "creating recurring event... -  ui not implemented yet";
            return result;
        });
        commands.push_back(make_shared<CustomCommand>(recurring));
    }

    std::vector<std::shared_ptr<Command>> executeAction(const std::vector<std::string> &parameters) override {
        if (!parameters.empty())
            for (const auto &command : commands) {
                if (command->name == parameters[0])
                    return command->executeAction(std::vector<std::string>(parameters.begin() + 1, parameters.end()));
            }
        return commands;
    };
};


#endif
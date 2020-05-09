/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 09.05.2020
 */

#ifndef CALENDAR_APP_COMMANDS_HELP_COMMAND
#define CALENDAR_APP_COMMANDS_HELP_COMMAND

#include "Command.h"
#include <utility>
#include <vector>
#include <memory>

class HelpCommand : public Command {
public:
    HelpCommand(const std::vector<std::unique_ptr<Command>> &commands_, std::ostream &out_) : Command("help", "", out_), commands(commands_) {

    }

    outcome executeAction(std::vector<std::string> parameters) override {
        for (const auto &command : commands) {
            out << *command << std::endl;
        }
        return outcome::Success;
    }

private:
    const std::vector<std::unique_ptr<Command>> &commands;
};

#endif


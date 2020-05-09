/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 09.05.2020
 */

#ifndef CALENDAR_APP_COMMANDS_CREATE_COMMAND
#define CALENDAR_APP_COMMANDS_CREATE_COMMAND

#include <utility>
#include <vector>
#include "Command.h"

class CreateCommand : public Command {
public:
    CreateCommand(std::ostream &out) : Command("create", "test", out) {}

    outcome executeAction(std::vector<std::string> parameters) override {
        return outcome::Failed;
    };
private:
};

#endif
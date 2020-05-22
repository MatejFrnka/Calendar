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
#include "../../Utility/InputUtility.h"

class CreateCommand : public Command {
public:
    CreateCommand(InputUtility &inputUtility, EventManager &eventManager);

    std::vector<std::shared_ptr<Command>> executeAction(const std::vector<std::string> &parameters) override;
};


#endif
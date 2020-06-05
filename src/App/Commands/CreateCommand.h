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

    std::vector<std::shared_ptr<Command>> executeAction(std::queue<std::string> &parameters) override;

private:
    EventManager &eventManager;

    bool createSingle(queue<std::string> &params) const;

    bool createRecurring(queue<std::string> &params) const;

    bool moveToFree(shared_ptr<Event> event) const;
};


#endif
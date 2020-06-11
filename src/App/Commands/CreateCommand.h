/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 09.05.2020
 */

#pragma once
#include <utility>
#include <vector>
#include "Command.h"
#include "../../Calendar/EventManager.h"
#include "../../Utility/InputUtility.h"

class CreateCommand : public Command {
public:
    CreateCommand(InputUtility &inputUtility, EventManager &eventManager);

    std::vector<std::shared_ptr<Command>> executeAction(std::queue<std::string> &parameters) override;

private:
    EventManager &eventManager;

    bool createSingle(std::queue<std::string> &params) const;

    bool createRecurring(std::queue<std::string> &params) const;

    bool moveToFree(std::shared_ptr<Event> event) const;
};



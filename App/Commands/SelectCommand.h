/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 26.05.2020
 */

#ifndef CALENDAR_SELECTCOMMAND_H
#define CALENDAR_SELECTCOMMAND_H


#include "Command.h"
#include "../../Calendar/EventManager.h"

class SelectCommand : public Command {
public:
    SelectCommand(InputUtility &inputUtility, EventManager &eventManager);

    std::vector<std::shared_ptr<Command>> executeAction(const std::vector<std::string> &parameters) override;
};


#endif //CALENDAR_SELECTCOMMAND_H

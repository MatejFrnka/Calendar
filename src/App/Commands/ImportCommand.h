/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 11.06.2020
 */

#ifndef CALENDAR_IMPORTCOMMAND_H
#define CALENDAR_IMPORTCOMMAND_H

#include "Command.h"
#include "../../Calendar/EventManager.h"
#include "../../Utility/FileUtility.h"

class ImportCommand : public Command {
public:
    ImportCommand(InputUtility &inputUtility, EventManager &eventManager_) : Command("import", "Imports events", inputUtility), eventManager(eventManager_) {};

    std::vector<std::shared_ptr<Command>> executeAction(std::queue<std::string> &parameters) override;

private:
    EventManager &eventManager;
};

std::vector<std::shared_ptr<Command>> ImportCommand::executeAction(std::queue<std::string> &parameters) {
    std::string path = inputUtility.readString("Full path", parameters);
    FileUtility::load(eventManager, inputUtility.out, path);
    return commands;
}

#endif //CALENDAR_IMPORTCOMMAND_H

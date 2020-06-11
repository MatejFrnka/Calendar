/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 11.06.2020
 */

#pragma once
#include "Command.h"
#include "../../Calendar/EventManager.h"
#include "../../Utility/FileUtility.h"

class ExportCommand : public Command {
public:
    ExportCommand(InputUtility &inputUtility, EventManager &eventManager_) : Command("export", "Exports all commands", inputUtility), eventManager(eventManager_) {};

    std::vector<std::shared_ptr<Command>> executeAction(std::queue<std::string> &parameters) override;

private:
    EventManager &eventManager;
};

std::vector<std::shared_ptr<Command>> ExportCommand::executeAction(std::queue<std::string> &parameters) {
    std::string path = inputUtility.readString("Full path", parameters);
    if (FileUtility::saveData(eventManager.exportEvents(), path))
        inputUtility.success();
    else
        inputUtility.out << "Could not save to that location";
    return commands;
}



/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 10.05.2020
 */

#pragma once
#include "../Command.h"
#include <utility>
#include "../../../Calendar/Event.h"
#include "../../../Calendar/EventManager.h"

class DeleteCommand : public Command {
public:
    DeleteCommand(InputUtility &inputUtility_, std::shared_ptr<Event> toDelete_, EventManager &eventManager_) :
            Command("delete", "Deletes an event", inputUtility_),
            target(std::move(toDelete_)),
            eventManager(eventManager_) {}

    DeleteCommand(const DeleteCommand &) = delete;

    std::vector<std::shared_ptr<Command>> executeAction(std::queue<std::string> &parameters) override {
        eventManager.removeEvent(target, inputUtility.readActionType(target->getActionTypes()));
        inputUtility.out << "Event " << target->getTitle() << " deleted" << std::endl;
        return commands;
    };
private:
    std::shared_ptr<Event> target;
    EventManager &eventManager;
};

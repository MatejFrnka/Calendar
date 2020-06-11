/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 01.06.2020
 */

#ifndef CALENDAR_MOVECOMMAND_H
#define CALENDAR_MOVECOMMAND_H

#include "../Command.h"
#include "../../../Calendar/EventManager.h"

class MoveCommand : public Command {
public:
    MoveCommand(InputUtility &inputUtility_, std::shared_ptr<Event> toMove_, EventManager &eventManager_) :
            Command("move", "Moves an event", inputUtility_),
            target(std::move(toMove_)),
            eventManager(eventManager_) {}

    MoveCommand(const MoveCommand &) = delete;

    std::vector<std::shared_ptr<Command>> executeAction(std::queue<std::string> &parameters) override {
        auto newStart = inputUtility.readDateTime("New Start", parameters);
        if (!eventManager.moveEvent(target, newStart)) {
            inputUtility.out << "Another event is happening during this time" << std::endl;
        } else
            inputUtility.success();
        return commands;
    };
private:
    std::shared_ptr<Event> target;
    EventManager &eventManager;
};

#endif //CALENDAR_MOVECOMMAND_H

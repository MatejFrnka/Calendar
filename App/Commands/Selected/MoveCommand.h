/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 26.05.2020
 */

#ifndef CALENDAR_MOVECOMMAND_H
#define CALENDAR_MOVECOMMAND_H

#include "../Command.h"
#include "../../../Calendar/EventManager.h"

class MoveCommand : public Command {
public:
    MoveCommand(InputUtility &inputUtility_, shared_ptr<Event> toDelete_, EventManager &eventManager_) :
            Command("move", "Moves an event", inputUtility_),
            toMove(std::move(toDelete_)),
            eventManager(eventManager_) {}

    MoveCommand(const MoveCommand &) = delete;

    std::vector<std::shared_ptr<Command>> executeAction(const std::vector<std::string> &parameters) override {
        bool firstIter = true;
        time_t newTime;
        while (true) {
            newTime = inputUtility.readDateTime("New date", (parameters.size() > 1 && firstIter) ? "" : parameters[1]);
            firstIter = false;
            eventManager.moveEvent()
        }


        inputUtility.out << "Event " << toMove->getTitle() << " moved" << std::endl;
        return commands;
    };
private:
    shared_ptr<Event> toMove;
    EventManager &eventManager;
};

#endif //CALENDAR_MOVECOMMAND_H
/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 10.05.2020
 */

#ifndef CALENDAR_DELETECOMMAND_H
#define CALENDAR_DELETECOMMAND_H

#include "../Command.h"

#include <utility>
#include "../../../Calendar/Event.h"
#include "../../../Calendar/EventManager.h"

class DeleteCommand : public Command {
public:
    DeleteCommand(InputUtility &inputUtility_, shared_ptr<Event> toDelete_, EventManager &eventManager_) :
            Command("delete", "Deletes an event", inputUtility_),
            target(std::move(toDelete_)),
            eventManager(eventManager_) {}

    DeleteCommand(const DeleteCommand &) = delete;

    std::vector<std::shared_ptr<Command>> executeAction(const std::vector<std::string> &parameters) override {
        if (!parameters.empty()) {
            if (parameters[0] == "all")
                eventManager.removeEvent(target, Event::actionType::AllEvents);
            else if (parameters[0] == "single")
                eventManager.removeEvent(target, Event::actionType::OnlyThis);
            else if (parameters[0] == "upcoming")
                eventManager.removeEvent(target, Event::actionType::ThisAndNext);
            else {
                inputUtility.noParameterFound(parameters[0]);
                return commands;
            }
        } else
            eventManager.removeEvent(target);
        inputUtility.out << "Event " << target->getTitle() << " deleted" << std::endl;
        return commands;
    };
private:
    shared_ptr<Event> target;
    EventManager &eventManager;
};

#endif

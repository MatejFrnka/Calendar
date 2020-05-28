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

    std::vector<std::shared_ptr<Command>> executeAction(std::queue<std::string> &parameters) override {
        auto actions = target->getActionTypes();
        if (actions.size() > 1) {
            inputUtility.out << "How many events should be deleted";
            for (size_t i = 0; i < actions.size(); ++i) {
                if (actions[i] == Event::AllEvents)
                    inputUtility.out << '(' << i << ") " << "All events";
                if (actions[i] == Event::ThisAndNext)
                    inputUtility.out << '(' << i << ") " << "This and upcoming events";
                if (actions[i] == Event::OnlyThis)
                    inputUtility.out << '(' << i << ") " << "Only this event";
            }
            int input;
            while (true) {
                input = inputUtility.readNumber("Number");
                if (input >= 0 && input < actions.size())
                    break;
                inputUtility.numberDoesNotMatch();
            }
        }
        eventManager.removeEvent(target);
        inputUtility.out << "Event " << target->getTitle() << " deleted" << std::endl;
        return commands;
    };
private:
    shared_ptr<Event> target;
    EventManager &eventManager;
};

#endif

/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 01.06.2020
 */

#ifndef CALENDAR_DURATIONCOMMAND_H
#define CALENDAR_DURATIONCOMMAND_H


#include "../Command.h"
#include "../../../Calendar/EventManager.h"

class DurationCommand : public Command {
public:
    DurationCommand(InputUtility &inputUtility_, std::shared_ptr<Event> toChange_, EventManager &eventManager_) :
            Command("duration", "Changes duration of an event", inputUtility_),
            target(std::move(toChange_)),
            eventManager(eventManager_) {}

    DurationCommand(const DurationCommand &) = delete;

    std::vector<std::shared_ptr<Command>> executeAction(std::queue<std::string> &parameters) override {
        auto duration = inputUtility.readTimeSpan("New duration", parameters);
        if (!eventManager.changeDuration(target, duration)) {
            inputUtility.out << "Event collides with another event, cannot change duration" << std::endl;
        } else
            inputUtility.success();
        return commands;
    };
private:
    std::shared_ptr<Event> target;
    EventManager &eventManager;
};

#endif //CALENDAR_DURATIONCOMMAND_H

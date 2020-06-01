/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 10.05.2020
 */

#include <cstring>
#include "CreateCommand.h"

CreateCommand::CreateCommand(InputUtility &inputUtility, EventManager &eventManager_) :
        Command("create", "Used to create a new event",
                inputUtility,
                std::map<std::string, std::string>{
                        {"single",    "Creates single event"},
                        {"recurring", "Creates recurring event"},
                }),
        eventManager(eventManager_) {}

std::vector<std::shared_ptr<Command>> CreateCommand::executeAction(std::queue<std::string> &parameters) {
    if (parameters.empty()) {
        inputUtility.noParameterFound();
        return commands;
    }
    bool result = false;
    if (parameters.front() == "single") {
        parameters.pop();
        result = createSingle(parameters);
    } else if (parameters.front() == "recurring") {
        parameters.pop();
        result = createRecurring(parameters);
    } else {
        inputUtility.noParameterFound(parameters.front());
        parameters.pop();
    }
    if (result)
        inputUtility.out << "Event created" << endl;
    return commands;
}

bool CreateCommand::createSingle(std::queue<std::string> &params) const {
    //Gathering event info
    auto title = inputUtility.readString("Title", params);
    auto startUtc = inputUtility.readDateTime("Start", params);
    auto duration = inputUtility.readTimeSpan("Duration", params);

    if (!eventManager.addEvent(SingleEvent::getInstance(title, startUtc, duration))) {
        time_t firstFree = eventManager.findFreeSpace(startUtc, duration);
        tm tm_firstFree = *localtime(&firstFree);
        inputUtility.out << "Another event is happening during given time. Do you want to move event to next available time - "
                         << asctime(&tm_firstFree);
        if (inputUtility.readBool("Move event"))
            eventManager.addEvent(SingleEvent::getInstance(title, firstFree, duration));
        else
            return false;
    }
    return true;
}

bool CreateCommand::createRecurring(std::queue<std::string> &params) const {
    auto title = inputUtility.readString("Title", params);
    auto startUtc = inputUtility.readDateTime("Start", params);
    auto duration = inputUtility.readTimeSpan("Duration", params);
    auto timeBetween = inputUtility.readTimeSpan("Time between events", params);
    auto repeatTill = inputUtility.readDate("Repeat till", params, false);
    shared_ptr<RecurringEvent> event;
    if (repeatTill == -1)
        event = RecurringEvent::getInstance(title, startUtc, duration, timeBetween);
    else
        event = RecurringEvent::getInstance(title, startUtc, duration, timeBetween, repeatTill);
    if (!eventManager.addEvent(event))
        return false;
    return true;
}
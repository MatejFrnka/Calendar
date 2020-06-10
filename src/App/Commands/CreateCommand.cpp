/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 10.05.2020
 */

#include <cstring>
#include "CreateCommand.h"
#include "../../Calendar/SingleEvent.h"
#include "../../Calendar/RecurringEvent.h"

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
        inputUtility.success();
    else
        inputUtility.out << "Cancelled" << endl;
    return commands;
}

bool CreateCommand::createSingle(std::queue<std::string> &params) const {
    //Gathering event info
    auto title = inputUtility.readString("Title", params);
    auto startUtc = inputUtility.readDateTime("Start", params);
    auto duration = inputUtility.readTimeSpan("Duration", params);


    auto event = make_shared<SingleEvent>(title, startUtc, duration);

    if (!eventManager.addEvent(event)) {
        return moveToFree(event);
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
        event = make_shared<RecurringEvent>(title, startUtc, duration, timeBetween);
    else
        event = make_shared<RecurringEvent>(title, startUtc, duration, timeBetween, repeatTill);
    if (!eventManager.addEvent(event)) {
        return moveToFree(event);
    }
    return true;
}

bool CreateCommand::moveToFree(shared_ptr<Event> event) const {
    time_t firstFree = eventManager.findFreeSpace(event);
    if (firstFree == -1) {
        inputUtility.out << "Another event is happening during given time. Unfortunately, no free time to move this event to was found." << endl;
        return false;
    }
    tm tm_firstFree = *localtime(&firstFree);

    inputUtility.out << "Another event is happening during given time. Do you want to move event to next available time - " << asctime(&tm_firstFree);
    event->setStartDateUtc(firstFree);
    if (inputUtility.readBool("Move event"))
        return eventManager.addEvent(event);
    else
        return false;
}
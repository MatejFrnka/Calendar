/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 29.04.2020
 */

#include "EventManager.h"


EventSet EventManager::getEvents(time_t start, time_t end) {
    EventSet result;

    for (auto &singleEvent : singleEvents)
        if (singleEvent->isInRange(start, end))
            result.refInsert(singleEvent);
    for (auto &recurringEvent : recurringEvents) {
        EventSet events = recurringEvent->getEvents(start, end);
        result.refInsert(events.begin(), events.end());
    }
    return result;
}

void EventManager::addEvent(SingleEvent *event) {
    event->addReference();
    singleEvents.push_back(event);
}

void EventManager::addEvent(RecurringEvent *event) {
    event->addReference();
    recurringEvents.push_back(event);
}

RecurringEvent *EventManager::editThisAndNextEvent(RecurringEvent *eventToEdit) {
    RecurringEvent *result = eventToEdit->getCopy();
    recurringEvents.push_back(result);
    return result;
}

SingleEvent *EventManager::editThisOnly(RecurringItemEvent *eventToEdit) {
    SingleEvent *result = eventToEdit->getCopySingleEvent();
    //GETTING PARENT EVENT

    RecurringEvent *parentEvent = eventToEdit->parentEvent;

    //CREATING EVENT AFTER CURRENT EVENT
    RecurringEvent *nextEvent = parentEvent->getCopy();
    nextEvent->startDateUtc = eventToEdit->startDateUtc + parentEvent->timeBetweenEvents;

    parentEvent->repeatTill = eventToEdit->startDateUtc;
    parentEvent->repeatToInfinity = false;
    //ADDING TO EVENT LIST
    recurringEvents.push_back(nextEvent);
    singleEvents.push_back(result);
    return result;
}

EventManager::~EventManager() {
    for (SingleEvent *event : singleEvents) {
        event->removeReference();
    }
    for (RecurringEvent *event : recurringEvents) {
        event->removeReference();
    }
}



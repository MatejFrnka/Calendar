/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 29.04.2020
 */

#include "EventManager.h"


EventSet<Event> EventManager::getEvents(time_t start, time_t end) {
    EventSet<Event> result;

    for (auto &singleEvent : singleEvents)
        if (singleEvent->isInRange(start, end))
            result.refInsert(singleEvent);
    for (auto &recurringEvent : recurringEvents) {
        EventSet<Event> events = recurringEvent->getEvents(start, end);
        result.refInsert(events.begin(), events.end());
    }
    return result;
}

bool EventManager::addEvent(SingleEvent *event) {
    if (!checkAvailability(event->getStartDateUtc(), event->getEndDateUtc()))
        return false;
    event->addReference();
    singleEvents.push_back(event);
    return true;
}

bool EventManager::addEvent(RecurringEvent *event) {
    if (!checkAvailability(event->getStartDateUtc(), event->getEndDateUtc(), event->getTimeBetweenEvents(),
                           event->getRepeatTill()))
        return false;
    event->addReference();
    recurringEvents.push_back(event);
    return true;
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
    nextEvent->setStartDateUtc(eventToEdit->getStartDateUtc() + parentEvent->getTimeBetweenEvents());

    parentEvent->setRepeatTill(eventToEdit->getStartDateUtc());
    parentEvent->setRepeatToInfinity(false);
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

time_t EventManager::checkAvailability(time_t start, time_t end) {
    auto events = getEvents(start, end);
    if (events.empty())
        return -1;
    else
        return (*events.begin())->getStartDateUtc();
}

time_t EventManager::checkAvailability(time_t start, time_t end, time_t timeBetweenEvents, time_t repeatTill) {
    if (checkAvailability(start, end) != -1)
        return checkAvailability(start, end);
    //TODO: IMPLEMENT
    return true;
}

time_t EventManager::checkAvailability(time_t start, time_t end, time_t timeBetweenEvents) {
    if (checkAvailability(start, end) != -1)
        return checkAvailability(start, end);
    //TODO: IMPLEMENT
    return true;
}




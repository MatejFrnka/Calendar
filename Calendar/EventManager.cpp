/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 29.04.2020
 */

#include "EventManager.h"


EventSet<shared_ptr<Event>> EventManager::getEvents(time_t start, time_t end) {
    EventSet<shared_ptr<Event>> result;
    //binary search first relevant event
    auto firstEvent = lower_bound(singleEvents.begin(),
                                  singleEvents.end(),
                                  start,
                                  [](const shared_ptr<Event> &event, time_t start) { return event->getEndDateUtc() < start; });
    while (firstEvent != singleEvents.end()) {
        if ((*firstEvent)->isInRange(start, end))
            result.insert(*firstEvent);
            //break if event starts after range
        else if ((*firstEvent)->getStartDateUtc() > end)
            break;
        firstEvent++;
    }
    for (const auto &recurringEvent : recurringEvents) {
        EventSet<shared_ptr<Event>> events = recurringEvent->getEvents(start, end);
        result.insert(events.begin(), events.end());
        //break if event starts after range end
        if (recurringEvent->getStartDateUtc() > end)
            break;
    }
    return result;
}

bool EventManager::addEvent(const shared_ptr<SingleEvent> &event) {
    if (checkAvailability(event->getStartDateUtc(), event->getEndDateUtc()) != -1)
        return false;
    singleEvents.insert(event);
    return true;
}

bool EventManager::addEvent(const shared_ptr<RecurringEvent> &event) {
    if (!checkAvailability(event->getStartDateUtc(), event->getEndDateUtc(), event->getTimeBetweenEvents(),
                           event->getRepeatTill()))
        return false;
    recurringEvents.insert(event);
    return true;
}
/*
RecurringEvent *EventManager::editThisAndNextEvent(RecurringEvent *eventToEdit) {
    RecurringEvent *result = eventToEdit->getCopy();
    recurringEvents.push_back(result);
    return result;
}
*/
/*
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
*/

EventManager::~EventManager() {
    /*
    for (SingleEvent *event : singleEvents) {
        event->removeReference();
    }
    for (RecurringEvent *event : recurringEvents) {
        event->removeReference();
    }*/
}

time_t EventManager::checkAvailability(time_t start, time_t end) {
    auto events = getEvents(start, end);
    if (events.empty())
        return -1;
    else
        return (*events.begin())->getStartDateUtc();
}

time_t EventManager::checkAvailability(time_t start, time_t end, time_t timeBetweenEvents, time_t repeatTill) {
    for (auto &sEvent  :singleEvents) {
        if (sEvent->eventExists(start, end, timeBetweenEvents, repeatTill))
            return false;
    }
    for (auto &rEvent : recurringEvents) {
        if (rEvent->eventExists(start, end, timeBetweenEvents, repeatTill))
            return false;
    }
    return true;
}

time_t EventManager::checkAvailability(time_t start, time_t end, time_t timeBetweenEvents) {
    for (auto &sEvent  :singleEvents) {
        if (sEvent->eventExists(start, end, timeBetweenEvents))
            return false;
    }
    for (auto &rEvent : recurringEvents) {
        if (rEvent->eventExists(start, end, timeBetweenEvents))
            return false;
    }
    return true;
}

bool EventManager::removeEvent(const shared_ptr<Event> &event) {
    lower_bound(singleEvents.begin(), singleEvents.end(), event);
    return false;
}




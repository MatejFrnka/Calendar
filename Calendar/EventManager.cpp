//
// Created by Matej Frnka on 13.03.2020.
//

#include "EventManager.h"

vector<Event *> *EventManager::getEvents(time_t start, time_t end) {
    vector<Event *> *result = new vector<Event*>;

    for (auto &singleEvent : singleEvents)
        if (singleEvent->isInRange(start, end))
            result->push_back(singleEvent);
    for (auto &recurringEvent : recurringEvents) {
        vector<Event *> events = recurringEvent->getEvents(start, end);
        result->insert(result->end(), events.begin(), events.end());

    }
    return result;
}

void EventManager::addEvent(SingleEvent *event) {
    singleEvents.push_back(event);
}

void EventManager::addEvent(RecurringEvent *event) {
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



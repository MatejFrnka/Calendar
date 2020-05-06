/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 29.04.2020
 */

#include "EventManager.h"


bool EventManager::addEvent(const shared_ptr<SingleEvent> &event) {
    if (checkAvailability(event->getStartDateUtc(), event->getEndDateUtc()) != -1)
        return false;
    singleEvents.insert(event);
    return true;
}

bool EventManager::addEvent(const shared_ptr<RecurringEvent> &event) {
    if (!checkAvailability(event->getStartDateUtc(), event->getEndDateUtc(), event->getTimeBetweenEvents(), event->getRepeatTill()))
        return false;
    recurringEvents.insert(event);
    return true;
}


time_t EventManager::checkAvailability(time_t start, time_t end) const {
    for (EventsIterator i(singleEvents, recurringEvents); !i.end(); ++i) {
        shared_ptr<Event> event = (*i)->eventExists(start, end);
        if (event) {
            return event->getStartDateUtc();
        }
    }
    return -1;
}

time_t EventManager::checkAvailability(time_t start, time_t end, time_t timeBetweenEvents, time_t repeatTill) const {
    for (EventsIterator i(singleEvents, recurringEvents); !i.end(); ++i) {
        shared_ptr<Event> event = (*i)->eventExists(start, end, timeBetweenEvents, repeatTill);
        if (event) {
            return event->getStartDateUtc();
        }
    }
    return -1;
}

time_t EventManager::checkAvailability(time_t start, time_t end, time_t timeBetweenEvents) const {
    for (EventsIterator i(singleEvents, recurringEvents); !i.end(); ++i) {
        shared_ptr<Event> event = (*i)->eventExists(start, end, timeBetweenEvents);
        if (event) {
            return event->getStartDateUtc();
        }
    }
    return -1;
}

EventSet<shared_ptr<Event>> EventManager::getEvents(time_t start, time_t end) {
    EventSet<shared_ptr<Event>> result;
    //binary search first relevant event
    auto firstEvent = lower_bound(singleEvents.begin(),
                                  singleEvents.end(),
                                  start,
                                  [](const shared_ptr<Event> &event, time_t start) { return event->getEndDateUtc() < start; });
    while (*firstEvent && firstEvent != singleEvents.end()) {
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

void EventManager::removeEvent(const shared_ptr<Event> &event, Event::actionType actionType) {

    auto freeEvent = (event)->freeSelf(actionType);
    if (freeEvent == nullptr)
        return;
    //Binary search through single events
    auto eventIt = lower_bound(singleEvents.begin(), singleEvents.end(), event, [](const shared_ptr<SingleEvent> &a, const shared_ptr<Event> &b) { return *a < *b; });
    if ((*eventIt) == freeEvent) {
        singleEvents.erase(eventIt);
        return;
    }
    //Event was not found in single events - must be recurring item event
    auto recEventIt = lower_bound(recurringEvents.begin(), recurringEvents.end(), freeEvent,
                                  [](const shared_ptr<RecurringEvent> &a, const shared_ptr<Event> &b) { return *a < *b; });
    if (*recEventIt == freeEvent) {
        recurringEvents.erase(recEventIt);
    }
}




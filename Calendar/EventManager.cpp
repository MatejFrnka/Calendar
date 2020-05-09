/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 29.04.2020
 */

#include "EventManager.h"


bool EventManager::addEvent(const shared_ptr<SingleEvent> &event) {
    if (checkAvailability(event->getStartDateUtc(), event->getEndDateUtc()))
        return false;
    singleEvents.insert(event);
    return true;
}

bool EventManager::addEvent(const shared_ptr<RecurringEvent> &event) {
    if (checkAvailability(event->getStartDateUtc(), event->getEndDateUtc(), event->getTimeBetweenEvents(), event->getRepeatTill()))
        return false;
    recurringEvents.insert(event);
    return true;
}

shared_ptr<SingleEvent> EventManager::checkAvailability(time_t start, time_t end, time_t timeBetweenEvents, time_t repeatTill) const {
    for (EventsIterator i(singleEvents, recurringEvents); !i.end(); ++i) {
        shared_ptr<SingleEvent> event;
        if (timeBetweenEvents == -1)
            event = (*i)->eventExists(start, end);
        else if (repeatTill == -1)
            event = (*i)->eventExists(start, end, timeBetweenEvents);
        else
            event = (*i)->eventExists(start, end, timeBetweenEvents, repeatTill);
        if (event) {
            return event;
        }
    }
    return nullptr;
}

EventSet<shared_ptr<SingleEvent>> EventManager::getEvents(time_t start, time_t end) {
    EventSet<shared_ptr<SingleEvent>> result;
    //binary search first relevant event
    auto firstEvent = lower_bound(singleEvents.begin(),
                                  singleEvents.end(),
                                  start,
                                  [](const shared_ptr<SingleEvent> &event, time_t start) { return event->getEndDateUtc() < start; });
    while (*firstEvent && firstEvent != singleEvents.end()) {
        if ((*firstEvent)->isInRange(start, end))
            result.insert(*firstEvent);
        else if ((*firstEvent)->getStartDateUtc() > end) //break if event starts after range
            break;
        firstEvent++;
    }
    for (const auto &recurringEvent : recurringEvents) {
        EventSet<shared_ptr<SingleEvent>> events = recurringEvent->getEvents(start, end);
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
    shared_ptr<RecurringEvent> ev = nullptr;
    for (const auto &ptr  : recurringEvents) {
        if (ev == nullptr || ev->getStartDateUtc() < ptr->getStartDateUtc())
            ev = ptr;
    }
    //Event was not found in single events - must be recurring item event
    auto recEventIt = lower_bound(recurringEvents.begin(), recurringEvents.end(), freeEvent,
                                  [](const shared_ptr<RecurringEvent> &a, const shared_ptr<Event> &b) { return *a < *b; });
    if (*recEventIt == freeEvent) {
        recurringEvents.erase(recEventIt);
    }
}

bool EventManager::moveEvent(shared_ptr<SingleEvent> &event, time_t newStartDateUtc) {
    if (newStartDateUtc == -1)
        newStartDateUtc = findFreeSpace(event->getEndDateUtc(), event->getDurationUtc());
    removeEvent(event);

    if (checkAvailability(newStartDateUtc, newStartDateUtc + event->getDurationUtc()))
        return false;
    if (!event->isEditable())
        return false;
    event->setStartDateUtc(newStartDateUtc);
    addEvent(event);
    return true;
}

time_t EventManager::findFreeSpace(time_t start, time_t duration) const {
    //Top limit for event in case it is longer than time between recurring event that goes to infinity
    time_t timeMax = -1;
    for (const auto &event:recurringEvents) {
        if (event->isRepeatToInfinity() && event->getTimeBetweenEvents() - event->getDurationUtc() < duration) {
            if (timeMax == -1 || timeMax > event->getStartDateUtc())
                timeMax = event->getStartDateUtc();
        }
    }

    while (timeMax == -1 || start <= timeMax - duration) {
        auto event = checkAvailability(start, start + duration);
        if (event == nullptr)
            return start;
        start = event->getEndDateUtc();
    }
    return -1;
}




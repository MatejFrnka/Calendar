/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 29.04.2020
 */

#include "SingleEvent.h"
#include "EventManager.h"

bool EventManager::addEvent(const shared_ptr<Event> &event) {
    if (checkAvailability(*event))
        return false;
    events.insert(event);
    return true;
}

shared_ptr<SingleEvent> EventManager::checkAvailability(const Event &event) const {
    return event.checkCollision(events);
}

shared_ptr<SingleEvent> EventManager::checkAvailability(time_t start, time_t end) const {
    for (const auto &event:events) {
        auto check = event->eventExists(start, end);
        if (check)
            return check;
    }
    return nullptr;
}

EventSet<shared_ptr<SingleEvent>> EventManager::getEvents(time_t start, time_t end) {
    EventSet<shared_ptr<SingleEvent>> result;
    for (const auto &recurringEvent : events) {
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
    auto recEventIt = lower_bound(events.begin(), events.end(), freeEvent,
                                  [](const shared_ptr<Event> &a, const shared_ptr<Event> &b) { return *a < *b; });
    if (*recEventIt == freeEvent) {
        events.erase(recEventIt);
    }
}

bool EventManager::moveEvent(shared_ptr<SingleEvent> &event, time_t newStartDateUtc) {
    if (newStartDateUtc == -1)
        newStartDateUtc = findFreeSpace(event->getEndDateUtc(), event->getDurationUtc());
    removeEvent(event);

    if (checkAvailability(newStartDateUtc, newStartDateUtc + event->getDurationUtc()))
        return false;
    if (!event->getEditable())
        return false;
    event->setStartDateUtc(newStartDateUtc);
    addEvent(event);
    return true;
}

time_t EventManager::findFreeSpace(time_t start, time_t duration) const {
    for (size_t i = 0; i < 10000; ++i) {
        auto event = checkAvailability(start, start + duration);
        if (event == nullptr)
            return start;
        start = event->getEndDateUtc();
    }
    return -1;
}

shared_ptr<SingleEvent> EventManager::findByStart(time_t start) {
    auto events = getEvents(start, start + 1);
    if (!events.empty()) {
        return *events.begin();
    }
    return nullptr;
}

EventSet<shared_ptr<Event>> EventManager::findByTitle(const string &title) {
    EventSet<shared_ptr<Event>> result;
    for (const auto &event :events) {
        if (event->getTitle() == title)
            result.insert(event);
    }
    return result;
}

EventSet<shared_ptr<Event>> EventManager::findByAddress(const string &address) {
    EventSet<shared_ptr<Event>> result;
    for (const auto &event :events) {
        if (event->getLocation() == address)
            result.insert(event);
    }
    return result;
}



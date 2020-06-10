/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 29.04.2020
 */

#include "SingleEvent.h"
#include "EventManager.h"
#include "../Utility/FileUtility.h"

bool EventManager::addEvent(const string &input) {
    auto event = FileUtility::fromString(input);
    return addEvent(event);
}

bool EventManager::addEvent(const shared_ptr<Event> &event) {
    if (checkAvailability(*event))
        return false;
    events.insert(event);
    return true;
}

shared_ptr<Event> EventManager::checkAvailability(const Event &event) const {
    return event.checkCollision(events);
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

void EventManager::removeEvent(shared_ptr<Event> event, Event::actionType actionType) {
    auto freeEvent = (event)->freeSelf(actionType);
    auto recEventIt = lower_bound(events.begin(), events.end(), freeEvent,
                                  [](const shared_ptr<Event> &a, const shared_ptr<Event> &b) { return *a < *b; });

    if (recEventIt != events.end() && (*recEventIt)->getStartDateUtc() == freeEvent->getStartDateUtc()) {
        events.erase(recEventIt);
    }
}

bool EventManager::moveEvent(shared_ptr<Event> event, time_t newStartDateUtc) {
    event->saveState();
    removeEvent(event);
    event->setStartDateUtc(newStartDateUtc);
    if (event->checkCollision(events)) {
        event->restoreState();
        addEvent(event);
        return false;
    }
    addEvent(event);
    return true;
}

bool EventManager::changeDuration(shared_ptr<Event> event, time_t newDuration) {
    event->saveState();
    event->setDurationUtc(newDuration);
    removeEvent(event);
    if (event->checkCollision(events)) {
        event->restoreState();
        addEvent(event);
        return false;
    }
    addEvent(event);
    return true;
}

time_t EventManager::findFreeSpace(shared_ptr<Event> event) const {
    return event->findFreeSpace(events);
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

string EventManager::exportEvents() {
    stringstream result;
    for (const auto &event :events)
        result << event->exportEvent() << endl;
    return result.str();
}

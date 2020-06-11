/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 29.04.2020
 */

#include "SingleEvent.h"
#include "EventManager.h"
#include "../Utility/FileUtility.h"

bool EventManager::addEvent(const std::string &input) {
    auto event = FileUtility::fromString(input);
    return addEvent(event);
}

bool EventManager::addEvent(const std::shared_ptr<Event> &event) {
    if (checkAvailability(*event))
        return false;
    events.insert(event);
    return true;
}

std::shared_ptr<Event> EventManager::checkAvailability(const Event &event) const {
    return event.checkCollision(events);
}


EventSet<std::shared_ptr<SingleEvent>> EventManager::getEvents(time_t start, time_t end) {
    EventSet<std::shared_ptr<SingleEvent>> result;
    for (const auto &recurringEvent : events) {
        EventSet<std::shared_ptr<SingleEvent>> events = recurringEvent->getEvents(start, end);
        result.insert(events.begin(), events.end());
        //break if event starts after range end
        if (recurringEvent->getStartDateUtc() > end)
            break;
    }
    return result;
}

void EventManager::removeEvent(std::shared_ptr<Event> event, Event::actionType actionType) {
    auto freeEvent = (event)->freeSelf(actionType);
    auto recEventIt = lower_bound(events.begin(), events.end(), freeEvent,
                                  [](const std::shared_ptr<Event> &a, const std::shared_ptr<Event> &b) { return *a < *b; });

    if (recEventIt != events.end() && (*recEventIt)->getStartDateUtc() == freeEvent->getStartDateUtc()) {
        events.erase(recEventIt);
    }
}

bool EventManager::moveEvent(std::shared_ptr<Event> event, time_t newStartDateUtc) {
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

bool EventManager::changeDuration(std::shared_ptr<Event> event, time_t newDuration) {
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

time_t EventManager::findFreeSpace(std::shared_ptr<Event> event) const {
    return event->findFreeSpace(events);
}

std::shared_ptr<SingleEvent> EventManager::findByStart(time_t start) {
    auto events = getEvents(start, start + 1);
    if (!events.empty()) {
        return *events.begin();
    }
    return nullptr;
}

EventSet<std::shared_ptr<Event>> EventManager::findByTitle(const std::string &title) {
    EventSet<std::shared_ptr<Event>> result;
    for (const auto &event :events) {
        if (event->getTitle() == title)
            result.insert(event);
    }
    return result;
}

EventSet<std::shared_ptr<Event>> EventManager::findByAddress(const std::string &address) {
    EventSet<std::shared_ptr<Event>> result;
    for (const auto &event :events) {
        if (event->getLocation() == address)
            result.insert(event);
    }
    return result;
}

std::string EventManager::exportEvents() {
    std::stringstream result;
    for (const auto &event :events)
        result << event->exportEvent() << std::endl;
    return result.str();
}

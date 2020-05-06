/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 06.05.2020
 */

#pragma once

#include <memory>
#include <algorithm>
#include "./EventSet.h"
#include "../Calendar/Event.h"
#include "../Calendar/SingleEvent.h"
#include "../Calendar/RecurringEvent.h"

/**
 * Used for iterating through both singleEvents and recurringEvents
 */
class EventsIterator {
public:
    EventsIterator() = delete;

    EventsIterator(const EventsIterator &) = delete;

    EventsIterator &operator=(const EventsIterator &) = delete;

    EventsIterator(const EventSet<std::shared_ptr<SingleEvent>> &sEvents, const EventSet<std::shared_ptr<RecurringEvent>> &rEvents);

    void operator++();

    bool end() { return singleIt == singleEvents->end() && recIt == recurringEvents->end(); }

    std::shared_ptr<Event> operator*();

private:
    const EventSet<std::shared_ptr<SingleEvent>> *singleEvents;
    EventSet<std::shared_ptr<SingleEvent>>::const_iterator singleIt;
    const EventSet<std::shared_ptr<RecurringEvent>> *recurringEvents;
    EventSet<std::shared_ptr<RecurringEvent>>::const_iterator recIt;
};



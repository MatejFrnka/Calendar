/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 06.05.2020
 */

#include "EventsIterator.h"

EventsIterator::EventsIterator(const EventSet<std::shared_ptr<SingleEvent>> &sEvents, const EventSet<std::shared_ptr<RecurringEvent>> &rEvents) {
    singleEvents = &sEvents;
    recurringEvents = &rEvents;
    singleIt = singleEvents->begin();
    recIt = recurringEvents->begin();
}

void EventsIterator::operator++() {
    if (singleIt != singleEvents->end())
        singleIt++;
    else
        recIt++;

}

std::shared_ptr<Event> EventsIterator::operator*() {
    if (singleIt != singleEvents->end())
        return std::dynamic_pointer_cast<Event>(*singleIt);
    else
        return std::dynamic_pointer_cast<Event>(*recIt);
}


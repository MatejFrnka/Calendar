/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 30.04.2020
 */

#include "EventSet.h"

template<typename EventType>
void EventSet<EventType>::refInsert(EventType *event) {
    event->addReference();
    set<EventType *, comparator<EventType>>::insert(event);
}

template<typename EventType>
void EventSet<EventType>::refInsert(ITER begin, ITER end) {
    auto tmp_begin = begin;
    while (tmp_begin != end) {
        (*tmp_begin)->addReference();
        tmp_begin++;
    }
    this->insert(begin, end);
}

template<typename EventType>
void EventSet<EventType>::refErase(EventType *event) {
    this->erase(event);
    event->removeReference();
}

template<typename EventType>
void EventSet<EventType>::refErase(ITER position) {
    Event *e = (*position);
    this->erase(position);
    e->removeReference();
}

template<typename EventType>
void EventSet<EventType>::refErase(ITER begin, ITER end) {
    const size_t dist = std::distance(begin, end);
    auto *tmp_event = new EventType *[dist];
    size_t i = 0;
    for (auto it = begin; it != end; ++it) {
        tmp_event[i] = *it;
        i++;
    }
    //remove events from set
    this->erase(begin, end);
    //remove reference and delete unused events
    for (int j = 0; j < dist; ++j) {
        tmp_event[j]->removeReference();
    }
    delete[] tmp_event;
}

template<typename EventType>
EventSet<EventType>::~EventSet() {
    for (auto event : *this) {
        event->removeReference();
        event = nullptr;
    }
}

template<typename EventType>
EventSet<EventType> &EventSet<EventType>::operator=(const EventSet &eventSet) {
    if (&eventSet == this)
        return *this;

    this->refErase(this->begin(), this->end());
    this->refInsert(eventSet.begin(), eventSet.end());
    return *this;
}

template<typename EventType>
EventSet<EventType>::EventSet(const EventSet &eventSet) {
    this->refInsert(eventSet.begin(), eventSet.end());
}

template
class EventSet<Event>;

template
class EventSet<SingleEvent>;

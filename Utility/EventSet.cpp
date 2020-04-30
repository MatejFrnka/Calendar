/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 30.04.2020
 */

#include "EventSet.h"

void EventSet::refInsert(Event *event) {
    event->addReference();
    set<Event *, comparator>::insert(event);
}

void EventSet::refInsert(iterator begin, iterator end) {
    auto tmp_begin = begin;
    while (tmp_begin != end) {
        (*tmp_begin)->addReference();
        tmp_begin++;
    }
    set<Event *, comparator>::insert(begin, end);
}

void EventSet::refErase(Event *event) {
    set<Event *, comparator>::erase(event);
    event->removeReference();
}

void EventSet::refErase(iterator position) {
    Event *e = (*position);
    set<Event *, comparator>::erase(position);
    e->removeReference();
}

void EventSet::refErase(set<Event *, comparator>::iterator begin, set<Event *, comparator>::iterator end) {
    const size_t dist = std::distance(begin, end);
    auto *tmp_event = new Event *[dist];
    size_t i = 0;
    for (auto it = begin; it != end; ++it) {
        tmp_event[i] = *it;
        i++;
    }
    //remove events from set
    erase(begin, end);
    //remove reference and delete unused events
    for (int j = 0; j < dist; ++j) {
        tmp_event[j]->removeReference();
    }
    delete[] tmp_event;
}

EventSet::~EventSet() {
    for (auto event : *this) {
        event->removeReference();
        event = nullptr;
    }
}

EventSet &EventSet::operator=(const EventSet &eventSet) {
    if (&eventSet == this)
        return *this;

    this->refErase(this->begin(), this->end());
    this->refInsert(eventSet.begin(), eventSet.end());
    return *this;
}

EventSet::EventSet(const EventSet &eventSet) {
    this->refInsert(eventSet.begin(), eventSet.end());
}


/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 30.04.2020
 */
#pragma once

#include <set>
#include <functional>
#include <iostream>
#include <vector>
#include "../Calendar/Event.h"
#include "../Calendar/SingleEvent.h"
#include "../Calendar/RecurringEvent.h"
#include "../Calendar/RecurringItemEvent.h"

#define ITER typename set<EventType *, comparator<EventType>>::iterator

using namespace std;

template<typename EventType>
struct comparator {
    bool operator()(const EventType *lhs, const EventType *rhs) { return *lhs < *rhs; }
};

template<typename EventType>
class EventSet : public set<EventType *, comparator<EventType>> {
public:
    void refInsert(EventType *event);

    void refInsert(ITER begin, ITER end);

    void refErase(EventType *event);

    void refErase(ITER position);

    void refErase(ITER begin, ITER end);

    ~EventSet();

    EventSet &operator=(const EventSet &eventSet);

    EventSet(const EventSet &eventSet);

    EventSet() = default;

};
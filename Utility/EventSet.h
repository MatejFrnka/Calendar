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

using namespace std;

struct comparator {
    bool operator()(const Event *lhs, const Event *rhs) { return *lhs < *rhs; }
};

class EventSet : public set<Event *, comparator> {
public:
    void refInsert(Event *event);

    void refInsert(iterator begin, iterator end);

    void refErase(Event *event);

    void refErase(iterator position);

    void refErase(iterator begin, iterator end);

    ~EventSet();

    EventSet &operator=(const EventSet &eventSet);

    EventSet(const EventSet &eventSet);

    EventSet() = default;

};
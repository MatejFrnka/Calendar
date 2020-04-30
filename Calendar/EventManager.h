/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 29.04.2020
 */

#pragma once

#include "SingleEvent.h"
#include "RecurringEvent.h"
#include "../Utility/EventSet.h"

using namespace std;

class EventManager {
public:
    void addEvent(SingleEvent *event);

    void addEvent(RecurringEvent *event);

    EventSet getEvents(time_t start, time_t end);

    RecurringEvent *editThisAndNextEvent(RecurringEvent *eventToEdit);

    SingleEvent *editThisOnly(RecurringItemEvent *eventToEdit);

    ~EventManager();

    EventManager operator=(const EventManager &) = delete;

    EventManager(const EventManager &) = delete;

    EventManager() = default;

private:
    vector<SingleEvent *> singleEvents;
    vector<RecurringEvent *> recurringEvents;
};

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
    bool addEvent(SingleEvent *event);

    bool addEvent(RecurringEvent *event);

    bool checkAvailability(time_t start, time_t end);

    bool checkAvailability(time_t start, time_t end, time_t repeat, time_t repeatTill);

    EventSet<Event> getEvents(time_t start, time_t end);

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

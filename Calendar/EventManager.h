//
// Created by Matej Frnka on 13.03.2020.
//

#ifndef CALENDAR_EVENTMANAGER_H
#define CALENDAR_EVENTMANAGER_H

#include "../ProjectIncludes.h"
#include "CalendarIncludes.h"


class EventManager {
public:
    void addEvent(SingleEvent *event);

    void addEvent(RecurringEvent *event);

    vector<Event *> *getEvents(time_t start, time_t end);

    RecurringEvent *editThisAndNextEvent(RecurringEvent *eventToEdit);

    SingleEvent *editThisOnly(RecurringItemEvent *eventToEdit);

private:
    vector<SingleEvent *> singleEvents;
    vector<RecurringEvent *> recurringEvents;
};

#endif //CALENDAR_EVENTMANAGER_H

//
// Created by Matej Frnka on 13.03.2020.
//

#ifndef CALENDAR_EVENTMANAGER_H
#define CALENDAR_EVENTMANAGER_H

#include "../ProjectIncludes.h"
#include "CalendarIncludes.h"

struct EventsList {

    EventsList(vector<Event *> *event) { events = event; }

    vector<Event *> *events;

    ~EventsList() {
        for (Event *item : *events) {
            if (item->getTypeId() == Event::RecurringEventItemId)
                delete item;
        }
        delete events;
    }
};

class EventManager {
public:
    void addEvent(SingleEvent *event);

    void addEvent(RecurringEvent *event);

    EventsList *getEvents(time_t start, time_t end);

    RecurringEvent *editThisAndNextEvent(RecurringEvent *eventToEdit);

    SingleEvent *editThisOnly(RecurringItemEvent *eventToEdit);

    ~EventManager();

private:
    vector<SingleEvent *> singleEvents;
    vector<RecurringEvent *> recurringEvents;
};

#endif //CALENDAR_EVENTMANAGER_H

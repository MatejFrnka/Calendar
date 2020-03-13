//
// Created by Matej Frnka on 13.03.2020.
//

#ifndef CALENDAR_EVENTMANAGER_H
#define CALENDAR_EVENTMANAGER_H

#include "../ProjectIncludes.h"
#include "Event.h"
#include "SingleEvent.h"
#include "RecurringEvent.h"

class EventManager {
public:
    void addEvent(SingleEvent *event) {
        singleEvents.push_back(event);
    }

    void addEvent(RecurringEvent *event) {
        recurringEvents.push_back(event);
    }

    vector<Event *> getEvents(time_t start, time_t end) {
        vector<Event *> result;
        for (auto &singleEvent : singleEvents)
            if (isInRange(start, end, singleEvent))
                result.push_back(singleEvent);

        for (auto &recurringEvent : recurringEvents) {

        }

        return result;
    }

private:
    vector<SingleEvent *> singleEvents;
    vector<RecurringEvent *> recurringEvents;

    bool isInRange(time_t start, time_t end, Event *event) {
        return ((event->startDateUtc > start && event->startDateUtc < end)
                || (event->endDateUtc > start && event->endDateUtc < end)
                || (event->startDateUtc < start && event->endDateUtc > end));
    }
};


#endif //CALENDAR_EVENTMANAGER_H

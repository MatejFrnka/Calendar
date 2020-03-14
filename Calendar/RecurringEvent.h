//
// Created by Matej Frnka on 13.03.2020.
//

#ifndef CALENDAR_RECURRINGEVENT_H
#define CALENDAR_RECURRINGEVENT_H

#include "Event.h"
#include "RecurringItemEvent.h"
#include "SingleEvent.h"

class RecurringEvent : public Event {
public:
    RecurringEvent(string title_, time_t startDateUtc_, time_t endDateUtc_, time_t timeBetweenEvents_,
                   time_t repeatTill_);

    RecurringEvent(string title_, time_t startDateUtc_, time_t endDateUtc_, time_t timeBetweenEvents_);

    time_t getRepeatTill() const;

    time_t getTimeBetweenEvents() const;

    bool getRepeatToInfinity() const;

    vector<Event *> getEvents(time_t start, time_t end);

    time_t getFirstEventTime(time_t start);

    RecurringEvent *getCopy();
    SingleEvent * getCopySingleEvent();
    void UpdateSelf(RecurringEvent * reference);

    time_t repeatTill;
    bool repeatToInfinity;
    time_t timeBetweenEvents;
private:



    time_t roundUp(time_t numToRound, time_t multiple);
};


#endif //CALENDAR_RECURRINGEVENT_H

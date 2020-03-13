//
// Created by Matej Frnka on 13.03.2020.
//

#ifndef CALENDAR_RECURRINGEVENT_H
#define CALENDAR_RECURRINGEVENT_H

#include "Event.h"

class RecurringEvent : public Event {
public:
    RecurringEvent(string title_, time_t startDateUtc_, time_t endDateUtc_, time_t timeBetweenEvents_,
                   time_t repeatFrom_, time_t repeatTill_) : Event(std::move(title_), startDateUtc_, endDateUtc_) {
        repeatToInfinity = false;
        repeatFrom = repeatFrom_;
        repeatTill = repeatTill_;
        timeBetweenEvents = timeBetweenEvents_;
    }

    RecurringEvent(string title_, time_t startDateUtc_, time_t endDateUtc_, time_t timeBetweenEvents_,
                   time_t repeatFrom_) : Event(std::move(title_), startDateUtc_, endDateUtc_) {
        repeatToInfinity = true;
        repeatFrom = repeatFrom_;
        repeatTill = 0;
        timeBetweenEvents = timeBetweenEvents_;
    }

    time_t getRepeatFrom() {
        return repeatFrom;
    }

    time_t getRepeatTill() {
        return repeatTill;
    }

    time_t getTimeBetweenEvents() {
        return timeBetweenEvents;
    }

    bool getRepeatToInfinity() {
        return repeatToInfinity;
    }

    // vector<Event *> getEvents(time_t start, time_t end) {
    //
    // }

    time_t getFirstEvent(time_t start) {
        if (start > endDateUtc) {
            time_t timeDifference = start - endDateUtc;
            return roundUp(timeDifference, timeBetweenEvents);
        } else
            return startDateUtc;
    }

private:
    time_t repeatTill;
    bool repeatToInfinity;
    time_t timeBetweenEvents;

    time_t roundUp(time_t numToRound, time_t multiple) {
        if (multiple == 0)
            return numToRound;

        int remainder = numToRound % multiple;
        if (remainder == 0)
            return numToRound;

        return numToRound + multiple - remainder;
    }
};


#endif //CALENDAR_RECURRINGEVENT_H

/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 29.04.2020
 */

#pragma once

#include <string>
#include <vector>
#include "Event.h"
#include "SingleEvent.h"
#include "RecurringItemEvent.h"
#include "../Utility/EventSet.h"

using namespace std;

class RecurringEvent : public Event {
public:
    RecurringEvent(string title_, time_t startDateUtc_, time_t endDateUtc_, time_t timeBetweenEvents_,
                   time_t repeatTill_);

    RecurringEvent(string title_, time_t startDateUtc_, time_t endDateUtc_, time_t timeBetweenEvents_);

    time_t getRepeatTill() const;

    time_t getTimeBetweenEvents() const;

    bool getRepeatToInfinity() const;

    EventSet getEvents(time_t start, time_t end);

    time_t getFirstEventTime(time_t start);

    RecurringEvent *getCopy();

    SingleEvent *getCopySingleEvent();

    void UpdateSelf(RecurringEvent *reference);

    time_t repeatTill;
    bool repeatToInfinity;
    time_t timeBetweenEvents;

    int getTypeId() override { return Event::RecurringEventId; };

private:


    time_t roundUp(time_t numToRound, time_t multiple);
};

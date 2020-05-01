/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 29.04.2020
 */

#pragma once

#include "SingleEvent.h"
#include "RecurringEvent.h"

class RecurringEvent;

class RecurringItemEvent : public Event {
public:
    RecurringItemEvent(string title_, time_t startDateUtc_, time_t duration_, RecurringEvent *parentEvent_);

    RecurringEvent *parentEvent;

    SingleEvent *getCopySingleEvent();

    int getTypeId() override { return Event::RecurringEventItemId; };


private:

};

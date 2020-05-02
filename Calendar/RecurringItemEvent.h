/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 29.04.2020
 */

#pragma once

#include "SingleEvent.h"
#include "RecurringEvent.h"

class RecurringEvent;

class RecurringItemEvent : public SingleEvent {
public:
    RecurringItemEvent(string title_, time_t startDateUtc_, time_t duration_, RecurringEvent *parentEvent_);

    RecurringEvent *parentEvent;

    SingleEvent *getCopySingleEvent();

    virtual int getTypeId() { return Event::RecurringEventItemId; };


private:

};

/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 29.04.2020
 */

#pragma once

#include "RecurringEvent.h"

class RecurringEvent;

class RecurringItemEvent : public SingleEvent {
protected:
    RecurringItemEvent(string title_, time_t startDateUtc_, time_t duration_, shared_ptr<RecurringEvent> parentEvent_);

public:
    static shared_ptr<RecurringItemEvent> getInstance(string title_, time_t startDateUtc_, time_t duration_, shared_ptr<RecurringEvent> parentEvent_);

    shared_ptr<RecurringEvent> parentEvent;

    SingleEvent *getCopySingleEvent();

    virtual int getTypeId() { return Event::RecurringEventItemId; };


private:

};

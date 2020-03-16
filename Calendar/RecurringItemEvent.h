//
// Created by Matej Frnka on 13.03.2020.
//

#ifndef CALENDAR_RECURRINGITEMEVENT_H
#define CALENDAR_RECURRINGITEMEVENT_H

#include "RecurringItemEvent.h"
#include "CalendarIncludes.h"


class RecurringItemEvent : public Event {
public:
    RecurringItemEvent(string title_, time_t startDateUtc_, time_t endDateUtc_, RecurringEvent *parentEvent_);

    RecurringEvent *parentEvent;

    SingleEvent *getCopySingleEvent();

    int getTypeId() override { return Event::RecurringEventItemId; };
private:

};


#endif //CALENDAR_RECURRINGITEMEVENT_H

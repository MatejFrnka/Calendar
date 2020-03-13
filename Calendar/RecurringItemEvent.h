//
// Created by Matej Frnka on 13.03.2020.
//

#ifndef CALENDAR_RECURRINGITEMEVENT_H
#define CALENDAR_RECURRINGITEMEVENT_H

#include "Event.h"
#include "RecurringEvent.h"

class RecurringItemEvent : public Event {
public:
    RecurringItemEvent(string title_, time_t startDateUtc_, time_t endDateUtc_, Event *parentEvent_) : Event(
            std::move(title_), startDateUtc_, endDateUtc_){
        parentEvent = parentEvent_;
    }

private:
    Event *parentEvent;
};


#endif //CALENDAR_RECURRINGITEMEVENT_H

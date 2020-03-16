//
// Created by Matej Frnka on 13.03.2020.
//

#ifndef CALENDAR_SINGLEEVENT_H
#define CALENDAR_SINGLEEVENT_H

#include "./Event.h"

class SingleEvent : public Event {
public:
    SingleEvent(string title_, time_t startDateUtc_, time_t endDateUtc_);

    int getTypeId() override { return Event::SingleEventId; };
};

#endif //CALENDAR_SINGLEEVENT_H

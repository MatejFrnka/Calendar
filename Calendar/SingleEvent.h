/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 29.04.2020
 */

#pragma once

#include "./Event.h"

using namespace std;

class SingleEvent : public Event {
public:
    SingleEvent(string title_, time_t startDateUtc_, time_t duration_);

    virtual int getTypeId() { return Event::SingleEventId; };

    virtual Event *eventExists(time_t start, time_t end);

    virtual Event *eventExists(time_t start, time_t end, time_t repeat);

    virtual Event *eventExists(time_t start, time_t end, time_t repeat, time_t repeatTill);
};

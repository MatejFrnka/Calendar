/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 29.04.2020
 */

#pragma once

#include "./Event.h"
#include <memory>

using namespace std;

class SingleEvent : public Event {
protected:
    SingleEvent(string title_, time_t startDateUtc_, time_t duration_);

public:
    static shared_ptr<SingleEvent> getInstance(string title_, time_t startDateUtc_, time_t duration_);

    virtual int getTypeId() { return Event::SingleEventId; };

    virtual shared_ptr<Event> eventExists(time_t start, time_t end);

    virtual shared_ptr<Event> eventExists(time_t start, time_t end, time_t repeat);

    virtual shared_ptr<Event> eventExists(time_t start, time_t end, time_t repeat, time_t repeatTill);
};
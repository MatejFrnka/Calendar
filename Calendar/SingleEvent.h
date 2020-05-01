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

    int getTypeId() override { return Event::SingleEventId; };
};

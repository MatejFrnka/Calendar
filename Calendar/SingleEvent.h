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

    /**
     * Return event that happens during given time range
     * @param start Start of range. Events ending exactly at param start will not be included
     * @param End of range. Events starting exactly at param end will not be included
     * @return Event happening in given time range or null_ptr
     */
    shared_ptr<Event> eventExists(time_t start, time_t end) override;

    /**
     * Return event that happens during given time range
     * @param start Start of range. Events ending exactly at param start will not be included
     * @param End of range. Events starting exactly at param end will not be included
     * @param repeat Repetition of event. Time_t difference between start of events
     * @return Event happening in given time range or null_ptr
     */
    shared_ptr<Event> eventExists(time_t start, time_t end, time_t repeat) override;

    /**
     * Return event that happens during given time range
     * @param start Start of range. Events ending exactly at param start will not be included
     * @param End of range. Events starting exactly at param end will not be included
     * @param repeat Repetition of event. Time_t difference between start of events
     * @param repeatTill Time to repeat to. There will be no events happening past this time;
     * @return Event happening in given time range or null_ptr
     */
    shared_ptr<Event> eventExists(time_t start, time_t end, time_t repeat, time_t repeatTill) override;
};
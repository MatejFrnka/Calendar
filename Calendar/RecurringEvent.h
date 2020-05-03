/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 29.04.2020
 */

#pragma once

#include <string>
#include <vector>
#include "Event.h"
#include "SingleEvent.h"
#include "RecurringItemEvent.h"
#include "../Utility/Exceptions/EventNotInRecurringEvent.h"
#include "../Utility/EventSet.h"
#include <utility>
#include <memory>

class RecurringItemEvent;

using namespace std;

class RecurringEvent : public Event {
protected:
    RecurringEvent(string title_, time_t startDateUtc_, time_t duration_, time_t timeBetweenEvents_, time_t repeatTill_);

    RecurringEvent(string title_, time_t startDateUtc_, time_t duration_, time_t timeBetweenEvents_);

public:
    static shared_ptr<RecurringEvent> getInstance(string title_, time_t startDateUtc_, time_t duration_, time_t timeBetweenEvents_, time_t repeatTill_);

    static shared_ptr<RecurringEvent> getInstance(string title_, time_t startDateUtc_, time_t duration_, time_t timeBetweenEvents_);


    EventSet<shared_ptr<Event>> getEvents(time_t start, time_t end);

    RecurringEvent *getCopy() const;

    SingleEvent *getCopySingleEvent() const;

    void UpdateSelf(RecurringEvent *reference);

    int getTypeId() override { return Event::RecurringEventId; };

    virtual shared_ptr<Event> eventExists(time_t start, time_t end);

    virtual shared_ptr<Event> eventExists(time_t start, time_t end, time_t repeat);

    virtual shared_ptr<Event> eventExists(time_t start, time_t end, time_t repeat, time_t repeatTill_);

private:
    time_t TimeOfEvent(time_t start, time_t end, time_t repeat, time_t repeatTill_ = -1);

    shared_ptr<RecurringItemEvent> getSingle(time_t start);

    time_t repeatTill;
    bool repeatToInfinity;
    time_t timeBetweenEvents;
//GETTERS AND SETTERS
public:
    time_t getRepeatTill() const;

    void setRepeatTill(time_t repeatTill);

    bool isRepeatToInfinity() const;

    void setRepeatToInfinity(bool repeatToInfinity);

    time_t getTimeBetweenEvents() const;

    void setTimeBetweenEvents(time_t timeBetweenEvents);


};

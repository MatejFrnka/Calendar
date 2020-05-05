/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 29.04.2020
 */

#ifndef CALENDAR_RECURRING_EVENT
#define CALENDAR_RECURRING_EVENT

#include <string>
#include <vector>
#include "Event.h"
#include "SingleEvent.h"
#include "RecurringItemEvent.h"
#include "../Utility/Exceptions/EventNotInRecurringEvent.h"
#include "../Utility/EventSet.h"
#include <utility>
#include <memory>
#include <algorithm>
#include "SingleEvent.h"

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

    void UpdateSelf(RecurringEvent *reference);

    int getTypeId() override { return Event::RecurringEventId; };

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
    shared_ptr<Event> eventExists(time_t start, time_t end, time_t repeat, time_t repeatTill_) override;

    shared_ptr<Event> freeRecurringItemEvent(const shared_ptr<RecurringItemEvent> &event, actionType actionType);

    shared_ptr<RecurringEvent> getParentOfItem(const shared_ptr<RecurringItemEvent> &recurringItem);

    shared_ptr<RecurringEvent> getFirstNode();

//    RecurringEvent &operator=(const RecurringEvent &event);

    bool deleteThisNode();

private:
    shared_ptr<Event> freeOnlyOneRecurringItemEvent(const shared_ptr<RecurringItemEvent> &event);

    shared_ptr<Event> freeThisAndNextRecurringItemEvent(const shared_ptr<RecurringItemEvent> &event);

    shared_ptr<Event> freeAllRecurringItemEvent();

    bool  isValid();

    /**
     * Get first event that happens while this event is happening
     * @param start Start of event to check
     * @param end End of event to check
     * @param repeat Repetition of event (space between starts)
     * @param repeatTill_ Event will not repeat beyond this, value -1 for infinity. Default value is -1
     * @return first time of event specified by given parameters that happens during this class event
     */
    time_t TimeOfEvent(time_t start, time_t end, time_t repeat, time_t repeatTill_ = -1);

    shared_ptr<RecurringItemEvent> getSingle(time_t start);

    time_t repeatTill;
    bool repeatToInfinity;
    time_t timeBetweenEvents;
    shared_ptr<RecurringEvent> parentNode = nullptr;
    shared_ptr<RecurringEvent> childNode = nullptr;

//GETTERS AND SETTERS
public:
    time_t getRepeatTill() const;

    void setRepeatTill(time_t repeatTill);

    bool isRepeatToInfinity() const;

    void setRepeatToInfinity(bool repeatToInfinity);

    time_t getTimeBetweenEvents() const;

    void setTimeBetweenEvents(time_t timeBetweenEvents);

};

#endif
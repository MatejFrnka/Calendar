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

    /**
     * Returns events generated by RecurringEvent happening in given time.
     * Includes events not fully included. Eg. start of event happens before @param start but end happens between @param start and @param end
     * Events ending at the same time as @param start or starting at the same time as @param end will not be inlcuded
     * @param start Start of range
     * @param end End of range
     * @return Events generated by this class happening in given time range
     */
    EventSet<shared_ptr<Event>> getEvents(time_t start, time_t end) override;

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

    /**
     * Removes @param event from sequence of events generated by this
     * @param event event to free from sequence
     * @param actionType how many events to free
     * @return shared_ptr to freed event
     */
    shared_ptr<Event> freeRecurringItemEvent(const shared_ptr<RecurringItemEvent> &event, actionType actionType);

    /**
     * Gets RecurringEvent node that generated the event
     * @param recurringItem RecurringEvent to find parent of
     * @return shared_ptr to node of this Recurring Event that generated @param recurringItem
     */
    shared_ptr<RecurringEvent> getParentOfItem(const shared_ptr<RecurringItemEvent> &recurringItem);

    shared_ptr<RecurringEvent> getFirstNode();

//    RecurringEvent &operator=(const RecurringEvent &event);

private:
    /**
     * Deletes this node of RecurringEvent, If this is the first node, it instead replaces itself with the next
     * @return True if deleted, false if this is the last node of recurring event and cannot be deleted
     */
    bool deleteThisNode();

    /**
     * Make event independent of this RecurringEvent
     * @param event Event to make independent. Event must come from this Recurring Event
     * @return Freed event
     */
    shared_ptr<Event> freeOnlyOneRecurringItemEvent(const shared_ptr<RecurringItemEvent> &event);

    /**
     * Make event and all following events independent of this RecurringEvent
     * @param event Event to make independent. Event must come from this Recurring Event
     * @return Freed series of events
     */
    shared_ptr<RecurringEvent> freeThisAndNextRecurringItemEvent(const shared_ptr<RecurringItemEvent> &event);

    /**
     * Check if event start is less than repeat till
     * @return true if event is valid
     */
    bool isValid();

    /**
     * Get first event that happens while this event is happening
     * @param start Start of event to check
     * @param end End of event to check
     * @param repeat Repetition of event (space between starts)
     * @param repeatTill_ Event will not repeat beyond this, value -1 for infinity. Default value is -1
     * @return first time of event specified by given parameters that happens during this class event
     */
    time_t TimeOfEvent(time_t start, time_t end, time_t repeat, time_t repeatTill_ = -1);

    /**
     * Creates RecurringEventItem at given time from self
     * @param start Time when the event should start - time must correspond to times created by timeBetweenEvents, repeatTill and startDateUtc
     * @return Generated RecurringItemEvent
     */
    shared_ptr<RecurringItemEvent> getSingle(time_t start);

    //Time to repeat to, no events will happen after this - even if it starts before repeatTill
    time_t repeatTill;
    bool repeatToInfinity;
    //Time between eventStart of events made by this
    time_t timeBetweenEvents;
    //If recurring item event was removed from RecurringEvent, Recurring event gets split into multiple smaller RecurringEvents to not include the event anymore
    //Parent node - always has event start sooner than this
    shared_ptr<RecurringEvent> parentNode = nullptr;
    //Child node - always has event start after this repeatTill
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
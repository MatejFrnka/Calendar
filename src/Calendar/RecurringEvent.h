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
#include "../Utility/Exceptions/EventNotInRecurringEventException.h"
#include "../Utility/EventSet.h"
#include <utility>
#include <memory>
#include <algorithm>
#include "SingleEvent.h"

class RecurringItemEvent;

using namespace std;

class RecurringEvent : public Event {
public:
    /**
     * @throws invalid_argument if duration_ is less than 1 or if timeBetweenEvents_ is less than 1
     */
    RecurringEvent(string title_, time_t startDateUtc_, time_t duration_, time_t timeBetweenEvents_, time_t repeatTill_);
    /**
     * @throws invalid_argument if duration_ is less than 1 or if timeBetweenEvents_ is less than 1
     */
    RecurringEvent(string title_, time_t startDateUtc_, time_t duration_, time_t timeBetweenEvents_);

    RecurringEvent(const RecurringEvent &event);

    /**
     * @throws InvalidEventSequenceException if input is invalid
     */
    RecurringEvent(istringstream &input);

    RecurringEvent &operator=(const RecurringEvent &) = default;

    EventSet<shared_ptr<SingleEvent>> getEvents(time_t start, time_t end) override;

    shared_ptr<SingleEvent> eventExists(time_t start, time_t end) override;

    shared_ptr<SingleEvent> eventExists(time_t start, time_t end, time_t repeat, time_t repeatTill_) override;

    /**
     * Removes @param event from sequence of events generated by this
     * @param event event to free from sequence
     * @param actionType how many events to free
     * @return shared_ptr to freed event
     */
    shared_ptr<Event> freeRecurringItemEvent(const shared_ptr<RecurringItemEvent> &event, actionType actionType);

    virtual shared_ptr<Event> freeSelf(actionType actionType);

    string infoAll() const override;

    shared_ptr<Event> checkCollision(const EventSet<shared_ptr<Event>> &ev) const override;

    void saveState() override;

    void restoreState() override;

    string exportEvent() const override;

    time_t findFreeSpace(const EventSet<shared_ptr<Event>> &events) override;

private:
    shared_ptr<RecurringEvent> state;

    shared_ptr<RecurringEvent> getFirstNode();

    /**
     * Gets RecurringEvent node that generated the event
     * @param recurringItem RecurringEvent to find parent of
     * @return shared_ptr to node of this Recurring Event that generated @param recurringItem
     * @throws EventNotInRecurringEvent when event trying to be freed is not event generated by this recurring events repeat pattern
     */
    shared_ptr<RecurringEvent> getParentOfItem(const shared_ptr<RecurringItemEvent> &recurringItem);

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
    bool isValid() const;

    /**
     * Get first event that happens while this event is happening
     * @param start Start of event to check
     * @param end End of event to check
     * @param repeat Repetition of event (space between starts)
     * @param repeatTill_ Event will not repeat beyond this, value -1 for infinity. Default value is -1
     * @return first time of event specified by given parameters that happens during this class event
     */
    time_t TimeOfEvent(time_t start, time_t end, time_t repeat, time_t repeatTill_ = -1) const;

    /**
     * Creates RecurringEventItem at given time from self
     * @param start Time when the event should start - time must correspond to times created by timeBetweenEvents, repeatTill and startDateUtc
     * @return Generated RecurringItemEvent
     * @throws EventNotInRecurringEvent when event specified by start does not match any event generated by this recurring event or any of its nodes
     */
    shared_ptr<RecurringItemEvent> getSingle(time_t start);

    //Time to repeat to, no events will happen after this - even if it starts before repeatTill
    time_t repeatTill;
    bool repeatToInfinity;
    //Time between eventStart of events made by this
    time_t timeBetweenEvents;
    //If recurring item event was removed from RecurringEvent, Recurring event gets split into multiple smaller RecurringEvents to not include the event anymore
    //Parent node - always has event start sooner than this
    weak_ptr<RecurringEvent> parentNode;

    //Child node - always has event start after this repeatTill
    shared_ptr<RecurringEvent> childNode = nullptr;
//GETTERS AND SETTERS
public:
    time_t getRepeatTill() const;

    bool isRepeatToInfinity() const;

    time_t getTimeBetweenEvents() const;

    void setStartDateUtc(time_t startDateUtc) override;

    void setDurationUtc(time_t durationUtc) override;
};

#endif
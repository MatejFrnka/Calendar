/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 29.04.2020
 */

#pragma once

#include "SingleEvent.h"
#include "RecurringEvent.h"
#include "../Utility/EventSet.h"
#include <algorithm>
#include <memory>

using namespace std;

class EventManager {
public:
    enum actionType {
        AllEvents,
        ThisAndNext,
        OnlyThis
    };

    /**
     * @param event Adds event to collection of events
     * @return True if adding as successful, false if event collides with another
     */
    bool addEvent(const shared_ptr<SingleEvent> &event);

    /**
     * @param event Adds recurring event to collection of events
     * @return True if adding as successful, false if event collides with another
     */
    bool addEvent(const shared_ptr<RecurringEvent> &event);

    bool removeEvent(const shared_ptr<Event> &event);
    /**
     * Checks if there are any events happening in given time window. Events ending exactly at param start or starting at param end are not included
     * @param start Start of range. Events ending exactly at param start will not be included
     * @param end  End of range. Events starting exactly at param end will not be included
     * @return -1 if no events were found, else time_t of start of the first event
     */
    time_t checkAvailability(time_t start, time_t end);

    /**
     * Checks if there are any events happening in given time window. Events ending exactly at param start or starting at param end are not included
     * @param start Start of range. Events ending exactly at param start will not be included
     * @param end  End of range. Events starting exactly at param end will not be included
     * @param repeat Repetition of event. Time_t difference between start of events
     * @param repeatTill Time to repeat to. There will be no events happening past this time;
     * @return -1 if no events were found, else time_t of start of the first event
     */
    time_t checkAvailability(time_t start, time_t end, time_t repeat, time_t repeatTill);

    /**
     * Checks if there are any events happening in given time window. Events ending exactly at param start or starting at param end are not included
     * @param start Start of range. Events ending exactly at param start will not be included
     * @param end  End of range. Events starting exactly at param end will not be included
     * @param repeat Repetition of event. Time_t difference between start of events
     * @return -1 if no events were found, else time_t of start of the first event
     */
    time_t checkAvailability(time_t start, time_t end, time_t repeat);

    /**
     * Used to get events happening between specified time
     * @param start Start of range. Events ending exactly at param start will not be included
     * @param end End of range. Events starting exactly at param end will not be included
     * @return EventSet of events happening in given time range
     */
    EventSet<shared_ptr<Event>> getEvents(time_t start, time_t end);

    RecurringEvent *editThisAndNextEvent(RecurringEvent *eventToEdit);

    SingleEvent *editThisOnly(RecurringItemEvent *eventToEdit);

    ~EventManager();

    EventManager operator=(const EventManager &) = delete;

    EventManager(const EventManager &) = delete;

    EventManager() = default;

private:

    EventSet<shared_ptr<SingleEvent>> singleEvents;
    EventSet<shared_ptr<RecurringEvent>> recurringEvents;
};

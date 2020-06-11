/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 29.04.2020
 */

#pragma once
#include "Event.h"
#include "../Utility/EventSet.h"
#include <algorithm>
#include <memory>
#include <utility>

class EventManager {
public:

    /**
     * @param path Path to event file to add
     * @return True if adding as successful, false if event collides with another
     */
    bool addEvent(const std::string &input);

    /**
     * @param event Adds recurring event to collection of events
     * @return True if adding as successful, false if event collides with another
     */
    bool addEvent(const std::shared_ptr<Event> &event);

    /**
     * Removes event from event manager
     * @param event Event generated by getEvents function
     * @param actionType What events should this effect
     */
    void removeEvent(std::shared_ptr<Event> event, Event::actionType actionType = Event::actionType::OnlyThis);

    /**
     * Moves event to new position
     * @param event Event to move
     * @param newStartDateUtc New start time of event
     * @throws Event not editable exception when event is not editable
     * @return true if success, false if failed
     */
    bool moveEvent(std::shared_ptr<Event> event, time_t newStartDateUtc);

    /**
     * Changes duration of event
     * @param event Event to change duration of
     * @param newDuration Target duration
     * @throws EventNotEditableException when event is not editable
     * @return True if duration changed, false if not
     */
    bool changeDuration(std::shared_ptr<Event> event, time_t newDuration);

    /**
    * Checks if there are any events happening in given time window. Events ending exactly at param start or starting at param end are not included
    * @param event Event defining time window
    * @return nullptr if no events were found, else first event found
    */
    std::shared_ptr<Event> checkAvailability(const Event &event) const;

    /**
     * Used to get events happening between specified time
     * @param start Start of range. Events ending exactly at param start will not be included
     * @param end End of range. Events starting exactly at param end will not be included
     * @return EventSet of events happening in given time range
     */
    EventSet<std::shared_ptr<SingleEvent>> getEvents(time_t start, time_t end);

    /**
     * Finds events that exactly match given title
     * Search speed is linear
     * @return Set of events that have equal title to title
     */
    EventSet<std::shared_ptr<Event>> findByTitle(const std::string &title);

    /**
     * Finds events that exactly match given name
     * Search speed is linear
     * @return Set of events that have equal name to fullName
     */
    EventSet<std::shared_ptr<Event>> findByAddress(const std::string &address);

    /**
     * Finds events that is happening during given time
     * @param start Start of event
     * @return Shared pointer to event that starts at given time
     */
    std::shared_ptr<SingleEvent> findByStart(time_t start);

    /**
     * Used for exporting all event manager's events
     * @return std::string of events that can later be used to import events back
     */
    std::string exportEvents();

    EventManager operator=(const EventManager &) = delete;

    EventManager(const EventManager &) = delete;

    EventManager() = default;

    /**
     * Finds first next free space
     * @param event Event to find free space for
     * @return Start of next first free space, -1 if there is no space ever (caused by recurring events repeating to infinity)
     */
    time_t findFreeSpace(std::shared_ptr<Event> event) const;

private:
    EventSet<std::shared_ptr<Event>> events;
};


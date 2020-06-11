/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 29.04.2020
 */

#pragma once

#include <ctime>
#include <string>
#include <iostream>
#include <memory>
#include <vector>
#include <iomanip>
#include "../Utility/InheritableSharedFromThis.h"
#include "../Utility/EventSet.h"
#include "Person.h"
#include "../Utility/DatetimeUtility.h"

class SingleEvent;

class RecurringEvent;

/**
 * Class event should be stored in smart pointer
 */
class Event : public inheritable_enable_shared_from_this<Event> {
protected:
public:

    /**
     * @param title_ Title of event
     * @param startDateUtc_ start date of event
     * @param durationUtc_ duration of event
     * @throws invalid_argument if duration is smaller than 1
     */
    Event(std::string title_, time_t startDateUtc_, time_t durationUtc_);

    /**
     * @throws InvalidEventSequenceException if input is invalid
     */
    explicit Event(std::istringstream &input);

    Event(const Event &event);

    Event &operator=(const Event &event);

    enum actionType {
        AllEvents,
        ThisAndNext,
        OnlyThis
    };

    /**
     * Saves event state
     */
    virtual void saveState() = 0;

    /**
     * Restores event state from previously saved state
     */
    virtual void restoreState() = 0;

    /**
     * Finds first next free space
     * @param events List of events to find free space in
     * @return Start of next first free space, -1 if there is no space ever (caused by recurring events repeating to infinity)
     */
    virtual time_t findFreeSpace(const EventSet<std::shared_ptr<Event>> &events);

    /**
     * Returns events generated by event happening in given time.
     * Includes events not fully included. Eg. start of event happens before param start but end happens between param start and param end
     * Events ending at the same time as param start or starting at the same time as param end will not be inlcuded
     * @param start Start of range
     * @param end End of range
     * @return Events generated by this class happening in given time range
     */
    virtual EventSet<std::shared_ptr<SingleEvent>> getEvents(time_t start, time_t end) = 0;

    /**
     * Check if current event is in given range
     * @param rangeStart Start of range
     * @param rangeEnd End of range
     * @return True if this event is in range defined by rangeStart - rangeEnd
     */
    bool isInRange(time_t rangeStart, time_t rangeEnd) const;

    /**
     * Check if data range start-end is in range rangeStart-rangeEnd
     * @param start Beginning of event range
     * @param end End of event range
     * @param rangeStart Beginning of the range you want to check the event is in
     * @param rangeEnd End of the range you want to check the event is in
     * @return True if event defined by start - end is in range defined by rangeStart-rangeEnd, else false
     */
    bool isInRange(time_t start, time_t end, time_t rangeStart, time_t rangeEnd) const;

    /**
     * Return event that happens during given time range
     * @param start Start of range. Events ending exactly at param start will not be included
     * @param End of range. Events starting exactly at param end will not be included
     * @return Event happening in given time range or null_ptr
     */
    virtual std::shared_ptr<SingleEvent> eventExists(time_t start, time_t end) = 0;

    /**
     * Return event that happens during given time range
     * @param start Start of range. Events ending exactly at param start will not be included
     * @param End of range. Events starting exactly at param end will not be included
     * @param repeat Repetition of event. Time_t difference between start of events
     * @param repeatTill Time to repeat to. There will be no events happening past this time; Set repeat till to -1 for repeat to infinity
     * @return Event happening in given time range or null_ptr
     */
    virtual std::shared_ptr<SingleEvent> eventExists(time_t start, time_t end, time_t repeat, time_t repeatTill) = 0;

    /**
     * Removes event from all events it depends on
     * @param actionType How many events does function effect
     * @return shared_ptr to freed event, nullptr if event could not be freed
     */
    virtual std::shared_ptr<Event> freeSelf(actionType actionType) = 0;

    /**
     * @return actionTypes that can be applied for this event
     */
    virtual std::vector<actionType> getActionTypes();

    /**
     * Checks if event collides with other events
     * @param ev Events to check collisions with
     * @return pointer to first event this event collides with or null pointer if it doenst collide with any events
     */
    virtual std::shared_ptr<Event> checkCollision(const EventSet<std::shared_ptr<Event>> &ev) const = 0;

    /**
     * @return string that can later be used to import the event back
     */
    virtual std::string exportEvent() const;

    /**
     * Compares start dates of events
     * @param event Event to compare this event with
     * @return true if this event's start date is smaller than other's event start date
     */
    bool operator<(const Event &event) const {
        return startDateUtc < event.startDateUtc;
    }

    friend std::ostream &operator<<(std::ostream &ostream, const Event &event) {
        time_t start = event.getStartDateUtc();
        tm time = *localtime(&start);
        ostream << "Date: " << DatetimeUtility::drawDate(time, DatetimeUtility::RangeTime::Day) << "\tTitle: " << event.getTitle();
        if (!event.getLocation().empty())
            ostream << "\tLocation: elect " << event.getLocation();
        return ostream;
    }

    /**
     * @return Info about event
     */
    virtual std::string infoAll() const = 0;

protected:
    /**
     * @return body of infoAll - it is the same for all events
     */
    std::string infoAllBody() const;

public:
    /**
     * @throws EventNotEditableException when editable is set to false
     */
    virtual bool addPerson(const std::shared_ptr<Person> &toAdd);

    /**
     * @throws EventNotEditableException when editable is set to false
     */
    virtual bool removePerson(const std::shared_ptr<Person> &toRemove);

    const std::vector<std::shared_ptr<Person>> &getPeople() const;

protected:

    /**
     * Get first event happening during or after time specified by startFrom
     * @param startFrom Time during or after the event will happen
     * @param startDate Start of event
     * @param duration Duration of event
     * @param timeBetweenEvents Time between start of event repeats
     * @return Timestamp of start of event happening during or after given date
     */
    time_t getFirstEventTime(time_t startFrom, time_t startDate, time_t duration, time_t timeBetweenEvents) const;

public:
//SETTERS & GETTERS
    bool getEditable() const;

    /**
     * @throws EventNotEditableException when editable is set to false
     */
    virtual void setEditable(bool editable);

    const std::string &getTitle() const;

    /**
     * @throws EventNotEditableException when editable is set to false
     */
    virtual void setTitle(const std::string &title);

    time_t getStartDateUtc() const;

    /**
     * @throws EventNotEditableException when editable is set to false
     */
    virtual void setStartDateUtc(time_t startDateUtc);

    time_t getDurationUtc() const;

    /**
     * @throws EventNotEditableException when editable is set to false
     */
    virtual void setDurationUtc(time_t durationUtc);

    time_t getEndDateUtc() const;

    const std::string &getLocation() const;

    /**
     * @throws EventNotEditableException when editable is set to false
     */

    virtual void setLocation(const std::string &location);

protected:
    const char sep = ';';

    std::string sanitize(const std::string &input) const;

    std::string title;
    time_t startDateUtc;
    time_t durationUtc;
    bool editable;
    std::string location;
    std::vector<std::shared_ptr<Person>> people;
};

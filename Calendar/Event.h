/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 29.04.2020
 */

#ifndef CALENDAR_EVENT
#define CALENDAR_EVENT

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

using namespace std;

class SingleEvent;

class RecurringEvent;

class EventsIterator;

class Event : public inheritable_enable_shared_from_this<Event> {
protected:
    Event(string title_, time_t startDateUtc_, time_t endDateUtc_);

public:
    enum actionType {
        AllEvents,
        ThisAndNext,
        OnlyThis
    };

    Event() = delete;

    /**
     * Returns events generated by RecurringEvent happening in given time.
     * Includes events not fully included. Eg. start of event happens before @param start but end happens between @param start and @param end
     * Events ending at the same time as @param start or starting at the same time as @param end will not be inlcuded
     * @param start Start of range
     * @param end End of range
     * @return Events generated by this class happening in given time range
     */
    virtual EventSet<shared_ptr<SingleEvent>> getEvents(time_t start, time_t end) = 0;

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
    virtual shared_ptr<SingleEvent> eventExists(time_t start, time_t end) = 0;

    /**
     * Return event that happens during given time range
     * @param start Start of range. Events ending exactly at param start will not be included
     * @param End of range. Events starting exactly at param end will not be included
     * @param repeat Repetition of event. Time_t difference between start of events
     * @return Event happening in given time range or null_ptr
     */
    virtual shared_ptr<SingleEvent> eventExists(time_t start, time_t end, time_t repeat) = 0;

    /**
     * Return event that happens during given time range
     * @param start Start of range. Events ending exactly at param start will not be included
     * @param End of range. Events starting exactly at param end will not be included
     * @param repeat Repetition of event. Time_t difference between start of events
     * @param repeatTill Time to repeat to. There will be no events happening past this time; Set repeat till to -1 for repeat to infinity
     * @return Event happening in given time range or null_ptr
     */
    virtual shared_ptr<SingleEvent> eventExists(time_t start, time_t end, time_t repeat, time_t repeatTill) = 0;

    /**
     * Removes event from all events it depends on
     * @param actionType How many events does function effect
     * @return shared_ptr to freed event, nullptr if event could not be freed
     */
    virtual shared_ptr<Event> freeSelf(actionType actionType) = 0;

    virtual vector<actionType> getActionTypes();

    virtual shared_ptr<SingleEvent> checkCollision(EventsIterator &ev) const = 0;

    void exportEvent(const string &path);

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
    virtual string infoAll() = 0;

    bool addPerson(const shared_ptr<Person> &toAdd);

    bool removePerson(const shared_ptr<Person> &toRemove);

    const vector<shared_ptr<Person>> &getPeople();

protected:
    bool editable = true;

    /**
     * Get first event happening during or after time specified by startFrom
     * @param startFrom Time during or after the event will happen
     * @param startDate Start of event
     * @param duration Duration of event
     * @param timeBetweenEvents Time between start of event repeats
     * @return Timestamp of start of event happening during or after given date
     */
    time_t
    getFirstEventTime(time_t
                      startFrom,
                      time_t startDate, time_t
                      duration,
                      time_t timeBetweenEvents
    ) const;

public:
//SETTERS & GETTERS
    void setEditable(bool editable);

    bool isEditable() const;

    const string &getTitle() const;

    void setTitle(const string &title);

    time_t getStartDateUtc() const;

    void setStartDateUtc(time_t startDateUtc);

    time_t getDurationUtc() const;

    void setDurationUtc(time_t durationUtc);

    time_t getEndDateUtc() const;

    const string &getLocation() const;

    void setLocation(const string &location);

private:
    string title;
    time_t startDateUtc;
    time_t durationUtc;
    string location;
    vector<shared_ptr<Person>> people;
};

#endif
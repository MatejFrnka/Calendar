/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 29.04.2020
 */

#pragma once

#include <ctime>
#include <string>
#include <iostream>

using namespace std;

class Event {
public:
    enum Type {
        SingleEventId,
        RecurringEventId,
        RecurringEventItemId
    };

    Event(string title_, time_t startDateUtc_, time_t endDateUtc_);

    bool isInRange(time_t start, time_t end) const;

    void EditEvent(Event *event);

    virtual int getTypeId() = 0;

    int getDay(bool start) const;

    int getHour(bool start) const;

    int getMinute(bool start) const;

    virtual ~Event() = default;

    bool operator<(const Event &event) const {
        return startDateUtc < event.startDateUtc;
    }

    void addReference();

    Event *removeReference();

protected:
    int ref_cnt = 0;
    bool editable = true;
//SETTERS & GETTERS
public:
    const string &getTitle() const;

    void setTitle(const string &title);

    time_t getStartDateUtc() const;

    void setStartDateUtc(time_t startDateUtc);

    time_t getDurationUtc() const;

    void setDurationUtc(time_t durationUtc);

    time_t getEndDateUtc() const;

private:
    string title;
    time_t startDateUtc;
    time_t durationUtc;

    const tm *getTime(bool start) const;

    tm startTime;
    tm endTime;
};
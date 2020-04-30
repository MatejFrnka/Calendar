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

    time_t getDuration();

    string title;
    time_t startDateUtc;
    time_t endDateUtc;

    bool isInRange(time_t start, time_t end);

    void EditEvent(Event *event);

    virtual int getTypeId() = 0;

    int getDay(bool start);

    int getHour(bool start);

    int getMinute(bool start);

    virtual ~Event() = default;

    bool operator<(const Event &event) const {
        return startDateUtc < event.startDateUtc;
    }

    void addReference();

    Event * removeReference();

protected:
    int ref_cnt = 0;
private:

    tm *getTime(bool start);

    tm startTime;
    tm endTime;
};
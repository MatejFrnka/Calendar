//
// Created by Matej Frnka on 13.03.2020.
//
#ifndef CALENDAR_EVENT_H
#define CALENDAR_EVENT_H

#include "../ProjectIncludes.h"

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

private:
    tm *getTime(bool start);

    tm startTime;
    tm endTime;
};


#endif //CALENDAR_EVENT_H

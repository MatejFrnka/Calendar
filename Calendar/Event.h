//
// Created by Matej Frnka on 13.03.2020.
//
#ifndef CALENDAR_EVENT_H
#define CALENDAR_EVENT_H

#include "../ProjectIncludes.h"

class Event {
public:
    Event(string title_, time_t startDateUtc_, time_t endDateUtc_);

    time_t getDuration();

    string title;
    time_t startDateUtc;
    time_t endDateUtc;

    bool isInRange(time_t start, time_t end);

    void EditEvent(Event *event);

    virtual void MakeAbastract() {};


    int getDay(bool start);

private:
    tm getTime(bool start);

    tm startTime;
    tm endTime;
};


#endif //CALENDAR_EVENT_H

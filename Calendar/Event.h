//
// Created by Matej Frnka on 13.03.2020.
//
#ifndef CALENDAR_EVENT_H
#define CALENDAR_EVENT_H

#include "../ProjectIncludes.h"

class Event {
public:
    Event(string title_, time_t startDateUtc_, time_t endDateUtc_) {
        title = std::move(title_);
        startDateUtc = startDateUtc_;
        endDateUtc = endDateUtc_;
    }
    time_t getDuration(){
        return endDateUtc-startDateUtc;
    }
    string title;
    time_t startDateUtc;
    time_t endDateUtc;
    bool isInRange(time_t start, time_t end);
private:

protected:

};


#endif //CALENDAR_EVENT_H

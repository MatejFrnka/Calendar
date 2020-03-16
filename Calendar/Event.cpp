//
// Created by Matej Frnka on 13.03.2020.
//

#include "Event.h"

bool Event::isInRange(time_t start, time_t end) {
    return ((startDateUtc >= start && startDateUtc <= end)
            || (endDateUtc >= start && endDateUtc <= end)
            || (startDateUtc <= start && endDateUtc >= end));
}

Event::Event(string title_, time_t startDateUtc_, time_t endDateUtc_) {
    title = std::move(title_);
    startDateUtc = startDateUtc_;
    endDateUtc = endDateUtc_;
    startTime = *gmtime(&startDateUtc);
    endTime = *gmtime(&endDateUtc);
}

time_t Event::getDuration() {
    return endDateUtc - startDateUtc;
}

void Event::EditEvent(Event *event) {

}

tm *Event::getTime(bool start) {
    if (start) {
        return &startTime;
    } else {
        return &endTime;
    }
}

int Event::getDay(bool start) {
    return getTime(start)->tm_mday;
}

int Event::getHour(bool start) {
    return getTime(start)->tm_hour;
}

int Event::getMinute(bool start) {
    return getTime(start)->tm_min;
}
/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 29.04.2020
 */

#include "Event.h"

bool Event::isInRange(time_t start, time_t end) {
    //event starts in range
    if (startDateUtc >= start && startDateUtc < end)
        return true;
    //event ends in range
    if (endDateUtc > start && endDateUtc <= end)
        return true;
    // event happens through range but doesnt start or end in it
    if (startDateUtc <= start && endDateUtc >= end)
        return true;
    return false;
}

Event::Event(string title_, time_t startDateUtc_, time_t endDateUtc_) {
    title = std::move(title_);
    startDateUtc = startDateUtc_;
    endDateUtc = endDateUtc_;
    startTime = *gmtime(&startDateUtc);
    endTime = *gmtime(&endDateUtc);

    ref_cnt++;
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

void Event::addReference() {
    ref_cnt++;
//    cout << "+\tref_cnt: " << ref_cnt << endl;
}

Event *Event::removeReference() {
    ref_cnt--;
//    cout << title << "-\tref_cnt: " << ref_cnt << endl;
    if (ref_cnt <= 0) {
        delete this;
        return nullptr;
    }
    return this;
}

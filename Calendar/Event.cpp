/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 29.04.2020
 */

#include "Event.h"

bool Event::isInRange(time_t start, time_t end) const {
    //event starts in range
    if (getStartDateUtc() >= start && getStartDateUtc() < end)
        return true;
    //event ends in range
    if (getEndDateUtc() > start && getEndDateUtc() <= end)
        return true;
    // event happens through range but doesnt start or end in it
    if (getStartDateUtc() <= start && getStartDateUtc() >= end)
        return true;
    return false;
}

Event::Event(string title_, time_t startDateUtc_, time_t durationUtc_) {
    title = std::move(title_);
    startDateUtc = startDateUtc_;
    durationUtc = durationUtc_;

    ref_cnt++;
}

time_t Event::getDuration() const {
    return endDateUtc - startDateUtc;
}

void Event::EditEvent(Event *event) {

}

const tm *Event::getTime(bool start) const {
    if (start) {
        return &startTime;
    } else {
        return &endTime;
    }
}

int Event::getDay(bool start) const {
    return getTime(start)->tm_mday;
}

int Event::getHour(bool start) const {
    return getTime(start)->tm_hour;
}

int Event::getMinute(bool start) const {
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

const string &Event::getTitle() const {
    return title;
}

void Event::setTitle(const string &title) {
    Event::title = title;
}

time_t Event::getStartDateUtc() const {
    return startDateUtc;
}

void Event::setStartDateUtc(time_t startDateUtc) {
    Event::startDateUtc = startDateUtc;
}

time_t Event::getDurationUtc() const {
    return durationUtc;
}

void Event::setDurationUtc(time_t durationUtc) {
    Event::durationUtc = durationUtc;
}

time_t Event::getEndDateUtc() const {
    return startDateUtc + durationUtc;
}

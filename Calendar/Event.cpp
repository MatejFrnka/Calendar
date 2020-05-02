/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 29.04.2020
 */

#include "Event.h"

Event::Event(string title_, time_t startDateUtc_, time_t durationUtc_) {
    title = std::move(title_);
    startDateUtc = startDateUtc_;
    durationUtc = durationUtc_;

    //TODO: CREATE TM STRUCTS startTime and endTime

    ref_cnt++;
}

bool Event::isInRange(time_t rangeStart, time_t rangeEnd) const {
    return isInRange(getStartDateUtc(), getEndDateUtc(), rangeStart, rangeEnd);
}

/**
 * Check if data range start-end is in range rangeStart-rangeEnd
 * @param start Beginning of event range
 * @param end End of event range
 * @param rangeStart Beginning of the range you want to check the event is in
 * @param rangeEnd End of the range you want to check the event is in
 * @return True if event defined by start - end is in range defined by rangeStart-rangeEnd, else false
 */
bool Event::isInRange(time_t start, time_t end, time_t rangeStart, time_t rangeEnd) const {
    //event starts in range
    if (start >= rangeStart && start < rangeEnd)
        return true;
    //event ends in range
    if (end > rangeStart && end <= rangeEnd)
        return true;
    // event happens through range but doesnt start or end in it
    if (start <= rangeStart && end >= rangeEnd)
        return true;
    return false;
}

time_t Event::getFirstEventTime(time_t startFrom, time_t startDate, time_t duration, time_t timeBetweenEvents) const {
    if (startDate < startFrom) {
        time_t rndDown = ((startFrom - startDate) / timeBetweenEvents);
        time_t time = rndDown * timeBetweenEvents + startDate;
        if (time + duration <= startFrom)
            time += timeBetweenEvents;
        return time;
    } else
        return startDate;
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

bool Event::isEditable() const {
    return editable;
}

void Event::setEditable(bool editable) {
    Event::editable = editable;
}

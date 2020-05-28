/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 29.04.2020
 */

#include <sstream>
#include "Event.h"

Event::Event(string title_, time_t startDateUtc_, time_t durationUtc_) {
    title = move(title_);
    startDateUtc = startDateUtc_;
    durationUtc = durationUtc_;
}

bool Event::isInRange(time_t rangeStart, time_t rangeEnd) const {
    return isInRange(getStartDateUtc(), getEndDateUtc(), rangeStart, rangeEnd);
}


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

const string &Event::getLocation() const {
    return location;
}

void Event::setLocation(const string &location) {
    Event::location = location;
}

bool Event::addPerson(const shared_ptr<Person> &toAdd) {
    for (const auto &person : people) {
        if (toAdd == person)
            return false;
    }
    people.push_back(toAdd);
    return true;
}

bool Event::removePerson(const shared_ptr<Person> &toRemove) {
    for (auto personIt = people.begin(); personIt != people.end(); personIt++) {
        if (toRemove == *personIt) {
            people.erase(personIt);
            return true;
        }
    }
    return false;
}

vector<shared_ptr<Person>> Event::getPeople() {
    return people;
}

vector<Event::actionType> Event::getActionTypes() {
    return vector<Event::actionType>{Event::actionType::OnlyThis};
}
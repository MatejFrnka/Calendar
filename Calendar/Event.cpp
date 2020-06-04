/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 29.04.2020
 */

#include <sstream>
#include "Event.h"
#include "../Utility/Exceptions/EventNotEditableException.h"
#include "../Utility/FileUtility.h"
#include "../Utility/Exceptions/InvalidEventSequenceException.h"


Event::Event(string title_, time_t startDateUtc_, time_t durationUtc_) {
    title = move(title_);
    if (durationUtc_ <= 0)
        throw invalid_argument("Event must be at least 1 second long");
    startDateUtc = startDateUtc_;
    durationUtc = durationUtc_;
}

Event::Event(const Event &event) : Event(event.title, event.startDateUtc, event.durationUtc) {
    location = event.location;
    people = event.people;
}

Event::Event(istringstream &input) : Event("t", 0, 1) {
    title = FileUtility::readNext(input, sep);
    if (title.empty())
        throw InvalidEventSequenceException();
    input >> startDateUtc;
    if (input.fail() || input.get() != sep)
        throw InvalidEventSequenceException();
    input >> durationUtc;
    if (input.fail() || input.get() != sep || durationUtc <= 0)
        throw InvalidEventSequenceException();
    location = FileUtility::readNext(input, sep);
    int peopleAmount;
    input >> peopleAmount;
    if (input.fail() || input.get() != sep)
        throw InvalidEventSequenceException();
    for (int i = 0; i < peopleAmount; ++i) {
        string name = FileUtility::readNext(input, sep);
        string surname = FileUtility::readNext(input, sep);
        string phone = FileUtility::readNext(input, sep);
        string email = FileUtility::readNext(input, sep);
        if (name.empty() || surname.empty())
            throw InvalidEventSequenceException();
        shared_ptr<Person> person = make_shared<Person>(name, surname);
        person->phone = phone;
        person->email = email;
        people.push_back(person);
    }
}

string Event::exportEvent() const {
    stringstream result;
    result << sanitize(title) << sep
           << startDateUtc << sep
           << durationUtc << sep
           << sanitize(location) << sep
           << people.size() << sep;
    for (const auto &person : people) {
        result << sanitize(person->name) << sep
               << sanitize(person->surname) << sep
               << sanitize(person->phone) << sep
               << sanitize(person->email) << sep;
    }
    return result.str();
}

Event &Event::operator=(const Event &event) {
    if (&event == this)
        return *this;
    title = event.title;
    startDateUtc = event.startDateUtc;
    durationUtc = event.durationUtc;
    location = event.location;
    people = event.people;
    return *this;
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
    if (start < rangeStart && end > rangeEnd)
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
    if (!Event::editable)
        throw EventNotEditableException();
    Event::title = title;
}

time_t Event::getStartDateUtc() const {
    return startDateUtc;
}

void Event::setStartDateUtc(time_t startDateUtc) {
    if (!Event::editable)
        throw EventNotEditableException();
    Event::startDateUtc = startDateUtc;
}

time_t Event::getDurationUtc() const {
    return durationUtc;
}

void Event::setDurationUtc(time_t durationUtc) {
    if (!Event::editable)
        throw EventNotEditableException();
    Event::durationUtc = durationUtc;
}

time_t Event::getEndDateUtc() const {
    return startDateUtc + durationUtc;
}

bool Event::getEditable() const {
    return editable;
}

void Event::setEditable(bool editable) {
    if (!Event::editable)
        throw EventNotEditableException();
    Event::editable = editable;
}

const string &Event::getLocation() const {
    return location;
}

void Event::setLocation(const string &location) {
    if (!Event::editable)
        throw EventNotEditableException();
    Event::location = location;
}

bool Event::addPerson(const shared_ptr<Person> &toAdd) {
    if (!Event::editable)
        throw EventNotEditableException();
    for (const auto &person : people) {
        if (toAdd == person)
            return false;
    }
    people.push_back(toAdd);
    return true;
}

bool Event::removePerson(const shared_ptr<Person> &toRemove) {
    if (!Event::editable)
        throw EventNotEditableException();
    for (auto personIt = people.begin(); personIt != people.end(); personIt++) {
        if (toRemove == *personIt) {
            people.erase(personIt);
            return true;
        }
    }
    return false;
}

const vector<shared_ptr<Person>> &Event::getPeople() const {
    return people;
}

vector<Event::actionType> Event::getActionTypes() {
    return vector<Event::actionType>{Event::actionType::OnlyThis};
}

time_t Event::findFreeSpace(const EventSet<shared_ptr<Event>> &events) {
    time_t originalStart = startDateUtc;
    for (size_t i = 0; i < 10000; ++i) {
        auto event = checkCollision(events);
        if (!event) {
            time_t result = startDateUtc;
            startDateUtc = originalStart;
            return result;
        }
        startDateUtc = event->getEndDateUtc();
    }
    return -1;
}

string Event::sanitize(const string &input) const {
    stringstream res;
    for (const char &c : input) {
        if (c == '\\' || c == ';') {
            res << '\\';
        }
        res << c;
    }
    return res.str();
}


string Event::infoAllBody() const {
    tm time{};
    time_t start = getStartDateUtc();
    time = *localtime(&start);
    stringstream ss;

    ss << "Title:\t" << getTitle() << '\n'
       << "Start:\t" << asctime(&time);

    time_t end = getEndDateUtc();
    time = *localtime(&end);
    ss << "End:\t" << asctime(&time)
       << "Is editable:\t" << (getEditable() ? "true" : "false") << endl;
    ss << "Location:\t" << location << endl;
    if (!people.empty()) {
        ss << "People:" << endl;
        for (const auto &person : people)
            ss << *person << endl;
    }
    return ss.str();
}


/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 29.04.2020
 */

#include "RecurringItemEvent.h"

RecurringItemEvent::RecurringItemEvent(string title_, time_t startDateUtc_, time_t duration_, shared_ptr<RecurringEvent> parentEvent_)
        : SingleEvent(move(title_), startDateUtc_, duration_), parentEvent(move(parentEvent_)) {

}

struct mk_shared_RecurringItemEvent : RecurringItemEvent {
    mk_shared_RecurringItemEvent(string title_, time_t startDateUtc_, time_t duration_, shared_ptr<RecurringEvent> parentEvent_)
            : RecurringItemEvent(move(title_), startDateUtc_, duration_, move(parentEvent_)) {}
};

shared_ptr<RecurringItemEvent> RecurringItemEvent::getInstance(string title_, time_t startDateUtc_, time_t duration_, shared_ptr<RecurringEvent> parentEvent_) {
    return make_shared<mk_shared_RecurringItemEvent>(move(title_), startDateUtc_, duration_, move(parentEvent_));
}

shared_ptr<Event> RecurringItemEvent::freeSelf(Event::actionType actionType) {
    if (parentEvent) {
        auto result = parentEvent->freeRecurringItemEvent(downcasted_shared_from_this<RecurringItemEvent>(), actionType);
        this->parentEvent = nullptr;
        return result;
    }
    return shared_from_this();
}

vector<Event::actionType> RecurringItemEvent::getActionTypes() {
    if (parentEvent)
        return vector<Event::actionType>{Event::actionType::OnlyThis, Event::actionType::AllEvents, Event::actionType::ThisAndNext};
    return Event::getActionTypes();
}

bool RecurringItemEvent::addPerson(const shared_ptr<Person> &toAdd) {
    if (parentEvent) {
        if (!parentEvent->addPerson(toAdd))
            return false;
    }
    return Event::addPerson(toAdd);
}

bool RecurringItemEvent::removePerson(const shared_ptr<Person> &toRemove) {
    if (parentEvent) {
        if (!parentEvent->removePerson(toRemove))
            return false;
    }
    return Event::removePerson(toRemove);
}

void RecurringItemEvent::setEditable(bool editable) {
    if (parentEvent)
        parentEvent->setEditable(editable);
    Event::setEditable(editable);
}

void RecurringItemEvent::setTitle(const string &title) {
    if (parentEvent)
        parentEvent->setTitle(title);
    Event::setTitle(title);
}

void RecurringItemEvent::setStartDateUtc(time_t startDateUtc) {
    if (parentEvent)
        parentEvent->setStartDateUtc(startDateUtc);
    Event::setStartDateUtc(startDateUtc);
}

void RecurringItemEvent::setDurationUtc(time_t durationUtc) {
    if (parentEvent)
        parentEvent->setDurationUtc(durationUtc);
    Event::setDurationUtc(durationUtc);
}

void RecurringItemEvent::setLocation(const string &location) {
    if (parentEvent)
        parentEvent->setLocation(location);
    Event::setLocation(location);
}

string RecurringItemEvent::infoAll() const {
    stringstream ss;
    ss << "Type:\tItem of a Recurring event" << endl
       << SingleEvent::infoAllBody();
    return ss.str();
}

shared_ptr<Event> RecurringItemEvent::getCopy() {
    shared_ptr<RecurringItemEvent> res = make_shared<RecurringItemEvent>(*this);
    return res;
}

void RecurringItemEvent::saveState() {
    state = make_shared<RecurringItemEvent>(*this);
    if (parentEvent)
        parentEvent->saveState();
}

void RecurringItemEvent::restoreState() {
    *this = *state;
    if (parentEvent)
        parentEvent->restoreState();
}

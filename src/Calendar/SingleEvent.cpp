/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 29.04.2020
 */

#include <sstream>
#include "RecurringEvent.h"
#include "SingleEvent.h"

SingleEvent::SingleEvent(const SingleEvent &event) : Event(event) {
    state = event.state;
}

SingleEvent::SingleEvent(istringstream &input) : Event(input) {

}

SingleEvent::SingleEvent(string title_, time_t startDateUtc_, time_t duration_) : Event(move(title_),
                                                                                        startDateUtc_,
                                                                                        - -duration_) {}

SingleEvent &SingleEvent::operator=(const SingleEvent &event) {
    if (&event == this)
        return *this;
    Event::operator=(event);
    state = event.state;
    return *this;
}

shared_ptr<SingleEvent> SingleEvent::eventExists(time_t start, time_t end) {
    if (isInRange(start, end))
        return downcasted_shared_from_this<SingleEvent>();
    return nullptr;
}

shared_ptr<SingleEvent> SingleEvent::eventExists(time_t start, time_t end, time_t repeat, time_t repeatTill) {
    time_t duration = end - start;
    time_t firstEventTime = getFirstEventTime(getStartDateUtc(), start, duration, repeat);
    if (firstEventTime + duration > repeatTill && repeatTill != -1)
        return nullptr;
    if (isInRange(getStartDateUtc(), getEndDateUtc(), firstEventTime, firstEventTime + duration))
        return downcasted_shared_from_this<SingleEvent>();
    return nullptr;
}

shared_ptr<Event> SingleEvent::freeSelf(Event::actionType actionType) {
    return shared_from_this();
}

EventSet<shared_ptr<SingleEvent>> SingleEvent::getEvents(time_t start, time_t end) {
    EventSet<shared_ptr<SingleEvent>> result;
    if (isInRange(start, end))
        result.insert(downcasted_shared_from_this<SingleEvent>());
    return result;
}

string SingleEvent::infoAll() const {
    stringstream ss;
    ss << "Type:\tSingle Event" << endl
       << Event::infoAllBody();
    return ss.str();
}

shared_ptr<Event> SingleEvent::checkCollision(const EventSet<shared_ptr<Event>> &ev) const {
    for (const auto &event:ev) {
        auto res = event->eventExists(getStartDateUtc(), getEndDateUtc());
        if (res)
            return res;
    }
    return nullptr;
}


void SingleEvent::saveState() {
    state = make_shared<SingleEvent>(*this);
}

void SingleEvent::restoreState() {
    *this = *state;
}

string SingleEvent::exportEvent() const {
    stringstream result;
    result << "singleevent" << sep << Event::exportEvent();
    return result.str();
}

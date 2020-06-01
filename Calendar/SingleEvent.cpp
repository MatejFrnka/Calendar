/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 29.04.2020
 */

#include <sstream>
#include "../Utility/EventsIterator.h"
#include "RecurringEvent.h"
#include "SingleEvent.h"

SingleEvent::SingleEvent(string title_, time_t startDateUtc_, time_t duration_) : Event(move(title_),
                                                                                        startDateUtc_,
                                                                                        duration_) {

}

shared_ptr<SingleEvent> SingleEvent::eventExists(time_t start, time_t end) {
    if (isInRange(start, end))
        return downcasted_shared_from_this<SingleEvent>();
    return nullptr;
}

shared_ptr<SingleEvent> SingleEvent::eventExists(time_t start, time_t end, time_t repeat) {
    return eventExists(start, end, repeat, -1);
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

struct mk_shared_SingleEvent : SingleEvent {
    mk_shared_SingleEvent(string title_, time_t startDateUtc_, time_t duration_) : SingleEvent(move(title_), startDateUtc_, duration_) {}
};

shared_ptr<SingleEvent> SingleEvent::getInstance(string title_, time_t startDateUtc_, time_t duration_) {
    return make_shared<mk_shared_SingleEvent>(move(title_), startDateUtc_, duration_);
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

string SingleEvent::infoAll() {
    tm time{};
    time_t start = getStartDateUtc();
    time = *localtime(&start);
    stringstream ss;

    ss << "Title:\t" << getTitle() << '\n'
       << "Type:\tSingle Event\n"
       << "Start:\t" << asctime(&time);

    time_t end = getEndDateUtc();
    time = *localtime(&end);
    ss << "End:\t" << asctime(&time)
       << "Is editable:\t" << (getEditable() ? "true" : "false") << endl;
    return ss.str();
}

shared_ptr<SingleEvent> SingleEvent::checkCollision(EventsIterator &ev) const {
    for (; !ev.end(); ++ev) {
        auto res = (*ev)->eventExists(getStartDateUtc(), getEndDateUtc());
        if (res)
            return res;
    }
    return nullptr;
}

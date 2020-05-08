/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 29.04.2020
 */

#include "SingleEvent.h"

SingleEvent::SingleEvent(string title_, time_t startDateUtc_, time_t duration_) : Event(std::move(title_),
                                                                                        startDateUtc_,
                                                                                        duration_) {

}

shared_ptr<Event> SingleEvent::eventExists(time_t start, time_t end) {
    if (isInRange(start, end))
        return shared_from_this();
    return shared_ptr<Event>(nullptr);
}

shared_ptr<Event> SingleEvent::eventExists(time_t start, time_t end, time_t repeat) {
    return eventExists(start, end, repeat, -1);
}

shared_ptr<Event> SingleEvent::eventExists(time_t start, time_t end, time_t repeat, time_t repeatTill) {
    time_t duration = end - start;
    time_t firstEventTime = getFirstEventTime(getStartDateUtc(), start, duration, repeat);
    if (firstEventTime + duration > repeatTill && repeatTill != -1)
        return shared_ptr<Event>(nullptr);
    if (isInRange(getStartDateUtc(), getEndDateUtc(), firstEventTime, firstEventTime + duration))
        return shared_from_this();
    return nullptr;
}

struct mk_shared_SingleEvent : SingleEvent {
    mk_shared_SingleEvent(string title_, time_t startDateUtc_, time_t duration_) : SingleEvent(move(title_), startDateUtc_, duration_) {}
};

shared_ptr<SingleEvent> SingleEvent::getInstance(string title_, time_t startDateUtc_, time_t duration_) {
    return make_shared<mk_shared_SingleEvent>(move(title_), startDateUtc_, duration_);
}

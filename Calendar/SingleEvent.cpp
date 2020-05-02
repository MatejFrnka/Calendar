/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 29.04.2020
 */

#include "SingleEvent.h"

SingleEvent::SingleEvent(string title_, time_t startDateUtc_, time_t duration_) : Event(std::move(title_),
                                                                                        startDateUtc_,
                                                                                        duration_) {

}

Event *SingleEvent::eventExists(time_t start, time_t end) {
    if (isInRange(start, end))
        return this;
    return nullptr;
}

Event *SingleEvent::eventExists(time_t start, time_t end, time_t repeat) {
    time_t duration = end - start;
    time_t firstEventTime = getFirstEventTime(getStartDateUtc(), start, duration, repeat);
    if (isInRange(getStartDateUtc(), getEndDateUtc(), firstEventTime, firstEventTime + duration))
        return this;
    return nullptr;
}

Event *SingleEvent::eventExists(time_t start, time_t end, time_t repeat, time_t repeatTill) {
    time_t duration = end - start;
    time_t firstEventTime = getFirstEventTime(getStartDateUtc(), start, duration, repeat);
    if (firstEventTime + duration > repeatTill)
        return nullptr;
    if (isInRange(getStartDateUtc(), getEndDateUtc(), firstEventTime, firstEventTime + duration))
        return this;
    return nullptr;
}
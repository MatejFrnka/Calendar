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
    if (start >= getEndDateUtc())
        return nullptr;
    if (isInRange(getStartDateUtc() % repeat, getStartDateUtc() % repeat + getDurationUtc(), start % repeat,
                  end % repeat))
        return this;
    return nullptr;
}

Event *SingleEvent::eventExists(time_t start, time_t end, time_t repeat, time_t repeatTill) {
    time_t duration = end - start;
    time_t test = getFirstEventTime(getStartDateUtc(), start, duration, repeat);
    if (test + duration > repeatTill)
        return nullptr;
    bool a = isInRange(getStartDateUtc(), getEndDateUtc(), test, test + duration);
    if (a)
        return this;
    return nullptr;
    /*
    time_t f = (getStartDateUtc() - start) / repeat;
    time_t r_start = f * repeat;
    time_t r_end = r_start + end - start;
    if(r_end > repeatTill || r_start < start)
        return nullptr;
    bool e = isInRange(r_start, r_end);
    if (e)
        return this;
    return nullptr;*/
}
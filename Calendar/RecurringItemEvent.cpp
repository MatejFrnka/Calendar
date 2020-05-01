/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 29.04.2020
 */

#include "RecurringItemEvent.h"

RecurringItemEvent::RecurringItemEvent(string title_, time_t startDateUtc_, time_t duration_,
                                       RecurringEvent *parentEvent_)
        : Event(std::move(title_), startDateUtc_, duration_) {
    parentEvent = parentEvent_;
}

SingleEvent *RecurringItemEvent::getCopySingleEvent() {
    return new SingleEvent(getTitle(), getStartDateUtc(), getDurationUtc());
}


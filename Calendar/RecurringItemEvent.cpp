//
// Created by Matej Frnka on 13.03.2020.
//

#include "RecurringItemEvent.h"
#include "SingleEvent.h"

RecurringItemEvent::RecurringItemEvent(string title_, time_t startDateUtc_, time_t endDateUtc_, RecurringEvent *parentEvent_)
        : Event(
        std::move(title_), startDateUtc_, endDateUtc_) {
    parentEvent = parentEvent_;
}

SingleEvent *RecurringItemEvent::getCopySingleEvent() {
    return new SingleEvent(title, startDateUtc, endDateUtc);
}



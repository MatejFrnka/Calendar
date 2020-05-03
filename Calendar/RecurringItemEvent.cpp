/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 29.04.2020
 */

#include "RecurringItemEvent.h"

#include <utility>

RecurringItemEvent::RecurringItemEvent(string title_, time_t startDateUtc_, time_t duration_, shared_ptr<RecurringEvent> parentEvent_)
        : SingleEvent(std::move(title_), startDateUtc_, duration_), parentEvent(std::move(parentEvent_)) {

}

struct mk_shared_RecurringItemEvent : RecurringItemEvent {
    mk_shared_RecurringItemEvent(string title_, time_t startDateUtc_, time_t duration_, shared_ptr<RecurringEvent> parentEvent_)
            : RecurringItemEvent(move(title_), startDateUtc_, duration_, move(parentEvent_)) {}
};

shared_ptr<RecurringItemEvent> RecurringItemEvent::getInstance(string title_, time_t startDateUtc_, time_t duration_, shared_ptr<RecurringEvent> parentEvent_) {
    return make_shared<mk_shared_RecurringItemEvent>(move(title_), startDateUtc_, duration_, move(parentEvent_));
}
/*
SingleEvent *RecurringItemEvent::getCopySingleEvent() {
    return new SingleEvent(getTitle(), getStartDateUtc(), getDurationUtc());
}
*/

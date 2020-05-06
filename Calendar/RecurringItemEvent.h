/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 29.04.2020
 */

#ifndef CALENDAR_RECURRING_EVENT_ITEM
#define CALENDAR_RECURRING_EVENT_ITEM

#include "RecurringEvent.h"
#include <utility>

class RecurringEvent;

class RecurringItemEvent : public SingleEvent {
protected:
    RecurringItemEvent(string title_, time_t startDateUtc_, time_t duration_, shared_ptr<RecurringEvent> parentEvent_);

public:
    static shared_ptr<RecurringItemEvent> getInstance(string title_, time_t startDateUtc_, time_t duration_, shared_ptr<RecurringEvent> parentEvent_);

    RecurringItemEvent() = delete;

    /**
     * Removes event from its RecurringEvent parent
     * @param actionType How many events does function effect
     * @return shared_ptr to freed event, nullptr if event could not be freed
     */
    shared_ptr<Event> freeSelf(actionType actionType = actionType::OnlyThis) override;

private:
    shared_ptr<RecurringEvent> parentEvent;
};

#endif
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
public:
    /**
     * @param title_ Title of event
     * @param startDateUtc_ start date of event
     * @param durationUtc_ duration of event
     * @param parentEvent_ Recurring event that generated this event
     * @throws invalid_argument if duration is smaller than 1
     */
    RecurringItemEvent(std::string title_, time_t startDateUtc_, time_t duration_, std::shared_ptr<RecurringEvent> parentEvent_);

    RecurringItemEvent(std::shared_ptr<RecurringEvent>, time_t startDateUtc_);

    RecurringItemEvent() = delete;

    std::shared_ptr<Event> freeSelf(actionType actionType = actionType::OnlyThis) override;

    std::vector<Event::actionType> getActionTypes() override;

    std::string infoAll() const override;

    bool addPerson(const std::shared_ptr<Person> &toAdd) override;

    bool removePerson(const std::shared_ptr<Person> &toRemove) override;

    void setEditable(bool editable) override;

    void setTitle(const std::string &title) override;

    void setStartDateUtc(time_t startDateUtc) override;

    void setDurationUtc(time_t durationUtc) override;

    void setLocation(const std::string &location) override;

    void saveState() override;

    void restoreState() override;

private:
    std::shared_ptr<RecurringEvent> parentEvent;

    std::shared_ptr<RecurringItemEvent> state;
};

#endif
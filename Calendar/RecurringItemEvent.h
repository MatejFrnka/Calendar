/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 29.04.2020
 */

#ifndef CALENDAR_RECURRING_EVENT_ITEM
#define CALENDAR_RECURRING_EVENT_ITEM

#include "RecurringEvent.h"
#include <utility>

using namespace std;

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

    vector<Event::actionType> getActionTypes() override;

    string infoAll() const override;

    bool addPerson(const shared_ptr<Person> &toAdd) override;

    bool removePerson(const shared_ptr<Person> &toRemove) override;

    void setEditable(bool editable) override;

    void setTitle(const string &title) override;

    void setStartDateUtc(time_t startDateUtc) override;

    void setDurationUtc(time_t durationUtc) override;

    void setLocation(const string &location) override;

    shared_ptr<Event> getCopy() override;

    void saveState() override;

    void restoreState() override;

private:
    shared_ptr<RecurringEvent> parentEvent;

    shared_ptr<RecurringItemEvent> state;
};

#endif
/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 29.04.2020
 */

#ifndef CALENDAR_SINGLE_EVENT
#define CALENDAR_SINGLE_EVENT


#include "Event.h"
#include <memory>
#include <utility>
#include <string>

using namespace std;

class SingleEvent : public Event {
public:
    /**
     * @param title_ Title of event
     * @param startDateUtc_ start date of event
     * @param durationUtc_ duration of event
     * @throws invalid_argument if duration is smaller than 1
     */
    SingleEvent(string title_, time_t startDateUtc_, time_t duration_);

    SingleEvent(const SingleEvent &);

    /**
     * @throws InvalidEventSequenceException if input is invalid
     */
    explicit SingleEvent(istringstream &input);

    SingleEvent &operator=(const SingleEvent &event);

    EventSet<shared_ptr<SingleEvent>> getEvents(time_t start, time_t end) override;

    shared_ptr<SingleEvent> eventExists(time_t start, time_t end) override;

    shared_ptr<SingleEvent> eventExists(time_t start, time_t end, time_t repeat, time_t repeatTill) override;

    shared_ptr<Event> freeSelf(actionType actionType) override;

    shared_ptr<Event> checkCollision(const EventSet<shared_ptr<Event>> &ev) const override;

    string exportEvent() const override;

    string infoAll() const override;

    void saveState() override;

    void restoreState() override;

private:
    shared_ptr<SingleEvent> state;
};

#endif
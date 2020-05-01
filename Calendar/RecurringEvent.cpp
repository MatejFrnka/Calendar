/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 29.04.2020
 */

#include "RecurringEvent.h"

RecurringEvent::RecurringEvent(string title_, time_t startDateUtc_, time_t duration_, time_t timeBetweenEvents_,
                               time_t repeatTill_) : Event(std::move(title_), startDateUtc_, duration_),
                                                     repeatTill(repeatTill_),
                                                     timeBetweenEvents(timeBetweenEvents_),
                                                     repeatToInfinity(false) {

}

RecurringEvent::RecurringEvent(string title_, time_t startDateUtc_, time_t duration_, time_t timeBetweenEvents_)
        : Event(std::move(title_), startDateUtc_, duration_),
          repeatTill(0),
          timeBetweenEvents(timeBetweenEvents_),
          repeatToInfinity(true) {
}

EventSet<Event> RecurringEvent::getEvents(time_t start, time_t end) {
    EventSet<Event> result;
    time_t eventTime = getFirstEventTime(start);

    while ((repeatToInfinity || eventTime < repeatTill) && eventTime < end) {
        RecurringItemEvent *event = new RecurringItemEvent(getTitle(), eventTime, getDurationUtc(), this);
        result.insert(event);
        eventTime += timeBetweenEvents;
    }
    return result;
}

time_t RecurringEvent::getFirstEventTime(time_t start) const {
    time_t test = getStartDateUtc();
    bool test1 = test < start;

    if (test < start) {
        time_t rndDown = ((start - getStartDateUtc()) / timeBetweenEvents);
        time_t time = rndDown * timeBetweenEvents + getStartDateUtc();
        if (time + getDurationUtc() <= start)
            time += timeBetweenEvents;
        return time;
    } else
        return getStartDateUtc();
}

RecurringEvent *RecurringEvent::getCopy() const {

    RecurringEvent *result;
    if (repeatToInfinity)
        result = new RecurringEvent(getTitle(), getStartDateUtc(), getDurationUtc(), timeBetweenEvents);
    else
        result = new RecurringEvent(getTitle(), getStartDateUtc(), getDurationUtc(), timeBetweenEvents,
                                    repeatTill);
    return result;
}

SingleEvent *RecurringEvent::getCopySingleEvent() const {
    return new SingleEvent(getTitle(), getStartDateUtc(), getEndDateUtc());
}

void RecurringEvent::UpdateSelf(RecurringEvent *reference) {
    setTitle(reference->getTitle());
    setStartDateUtc(reference->getStartDateUtc());
    setDurationUtc(reference->getDurationUtc());
    timeBetweenEvents = reference->timeBetweenEvents;
    repeatTill = reference->repeatTill;
    repeatToInfinity = reference->repeatToInfinity;
    timeBetweenEvents = reference->timeBetweenEvents;
}

time_t RecurringEvent::getRepeatTill() const {
    return repeatTill;
}

void RecurringEvent::setRepeatTill(time_t repeatTill) {
    RecurringEvent::repeatTill = repeatTill;
}

bool RecurringEvent::isRepeatToInfinity() const {
    return repeatToInfinity;
}

void RecurringEvent::setRepeatToInfinity(bool repeatToInfinity) {
    RecurringEvent::repeatToInfinity = repeatToInfinity;
}

time_t RecurringEvent::getTimeBetweenEvents() const {
    return timeBetweenEvents;
}

void RecurringEvent::setTimeBetweenEvents(time_t timeBetweenEvents) {
    RecurringEvent::timeBetweenEvents = timeBetweenEvents;
}

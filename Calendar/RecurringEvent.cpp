/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 29.04.2020
 */

#include "RecurringEvent.h"

RecurringEvent::RecurringEvent(string title_, time_t startDateUtc_, time_t endDateUtc_, time_t timeBetweenEvents_,
                               time_t repeatTill_) : Event(std::move(title_), startDateUtc_, endDateUtc_) {
    repeatToInfinity = false;
    repeatTill = repeatTill_;
    timeBetweenEvents = timeBetweenEvents_;

}

RecurringEvent::RecurringEvent(string title_, time_t startDateUtc_, time_t endDateUtc_, time_t timeBetweenEvents_)
        : Event(std::move(title_), startDateUtc_, endDateUtc_) {
    repeatToInfinity = true;
    repeatTill = 0;
    timeBetweenEvents = timeBetweenEvents_;
}

time_t RecurringEvent::getRepeatTill() const {
    return repeatTill;
}

time_t RecurringEvent::getTimeBetweenEvents() const {
    return timeBetweenEvents;
}

bool RecurringEvent::getRepeatToInfinity() const {
    return repeatToInfinity;
}

EventSet<Event> RecurringEvent::getEvents(time_t start, time_t end) {
    EventSet<Event> result;
    time_t eventTime = getFirstEventTime(start);

    while ((repeatToInfinity || eventTime < repeatTill) && eventTime < end) {
        RecurringItemEvent *event = new RecurringItemEvent(title, eventTime, eventTime + getDuration(), this);
        result.insert(event);

        eventTime += timeBetweenEvents;
    }
    return result;
}

time_t RecurringEvent::getFirstEventTime(time_t start) const {
    if (startDateUtc < start) {
        //time_t timeDifference = start - startDateUtc;
        //time_t first = roundUp(timeDifference, timeBetweenEvents);
        time_t rndDown = ((start - startDateUtc) / timeBetweenEvents);
        time_t time = rndDown * timeBetweenEvents + startDateUtc;
        if (time + getDuration() <= start)
            time += timeBetweenEvents;
        return time;
    } else
        return startDateUtc;
}

RecurringEvent *RecurringEvent::getCopy() const {

    RecurringEvent *result;
    if (repeatToInfinity)
        result = new RecurringEvent(title, startDateUtc, endDateUtc, timeBetweenEvents);
    else
        result = new RecurringEvent(title, startDateUtc, endDateUtc, timeBetweenEvents,
                                    repeatTill);
    return result;
}

SingleEvent *RecurringEvent::getCopySingleEvent() const {
    return new SingleEvent(title, startDateUtc, endDateUtc);
}

void RecurringEvent::UpdateSelf(RecurringEvent *reference) {
    title = reference->title;
    startDateUtc = reference->startDateUtc;
    endDateUtc = reference->endDateUtc;
    timeBetweenEvents = reference->timeBetweenEvents;
    repeatTill = reference->repeatTill;
    repeatToInfinity = reference->repeatToInfinity;
    timeBetweenEvents = reference->timeBetweenEvents;
}
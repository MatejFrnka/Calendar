//
// Created by Matej Frnka on 13.03.2020.
//

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

vector<Event *> RecurringEvent::getEvents(time_t start, time_t end) {
    vector<Event *> result;
    time_t eventTime = getFirstEventTime(start);
    do {
        RecurringItemEvent *event = new RecurringItemEvent(title, eventTime, eventTime + getDuration(), this);
        result.push_back(event);

        eventTime += timeBetweenEvents;
    } while ((repeatToInfinity || eventTime < repeatTill)
             && eventTime < end);
    return result;
}

time_t RecurringEvent::getFirstEventTime(time_t start) {
    if (start > startDateUtc) {
        time_t timeDifference = start - startDateUtc;
        time_t first = roundUp(timeDifference, timeBetweenEvents);
        if (first + getDuration() > start)
            return first;
        else
            return first + timeBetweenEvents;
    } else
        return startDateUtc;
}

//Function by Mark Ransom, modified
//https://stackoverflow.com/a/3407254/9536240
//https://stackoverflow.com/users/5987/mark-ransom
time_t RecurringEvent::roundUp(time_t numToRound, time_t multiple) {
    if (multiple == 0)
        return numToRound;

    time_t remainder = numToRound % multiple;
    if (remainder == 0)
        return numToRound;

    return numToRound + multiple - remainder;
}

RecurringEvent *RecurringEvent::getCopy() {

    RecurringEvent *result;
    if (repeatToInfinity)
        result = new RecurringEvent(title, startDateUtc, endDateUtc, timeBetweenEvents);
    else
        result = new RecurringEvent(title, startDateUtc,endDateUtc, timeBetweenEvents,
                                    repeatTill);
    return result;
}

SingleEvent *RecurringEvent::getCopySingleEvent() {
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

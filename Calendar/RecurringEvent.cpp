/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 29.04.2020
 */

#include "RecurringEvent.h"


RecurringEvent::RecurringEvent(string title_, time_t startDateUtc_, time_t duration_, time_t timeBetweenEvents_,
                               time_t repeatTill_) : Event(std::move(title_), startDateUtc_, duration_) {
    timeBetweenEvents = timeBetweenEvents_;
    repeatTill = repeatTill_;
    repeatToInfinity = false;

}

RecurringEvent::RecurringEvent(string title_, time_t startDateUtc_, time_t duration_, time_t timeBetweenEvents_)
        : Event(std::move(title_), startDateUtc_, duration_) {
    timeBetweenEvents = timeBetweenEvents_;
    repeatTill = 0;
    repeatToInfinity = true;
}

EventSet<shared_ptr<Event>> RecurringEvent::getEvents(time_t start, time_t end) {
    EventSet<shared_ptr<Event>> result;
    time_t eventTime = getFirstEventTime(start, getStartDateUtc(), getDurationUtc(), getTimeBetweenEvents());

    while ((repeatToInfinity || eventTime < repeatTill) && eventTime < end) {
        result.insert(getSingle(eventTime));
        eventTime += timeBetweenEvents;
    }
    return result;
}

/*
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
*/
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

shared_ptr<Event> RecurringEvent::eventExists(time_t start, time_t end) {
    auto events = this->getEvents(start, end);
    if (!events.empty())
        return *events.begin();
    return shared_ptr<Event>(nullptr);
}

shared_ptr<Event> RecurringEvent::eventExists(time_t start, time_t end, time_t repeat) {
    time_t time = TimeOfEvent(start, end, repeat);
    if (time == -1)
        return shared_ptr<Event>(nullptr);
    time -= (time - getStartDateUtc()) % getTimeBetweenEvents();
    return getSingle(time);

}

shared_ptr<Event> RecurringEvent::eventExists(time_t start, time_t end, time_t repeat, time_t repeatTill_) {
    time_t time = TimeOfEvent(start, end, repeat, repeatTill_);
    if (time == -1)
        return shared_ptr<Event>(nullptr);
    time = (time - getStartDateUtc()) % getTimeBetweenEvents();
    return getSingle(time);
}

/**
 * Get first event that happens while this event is happening
 * @param start Start of event to check
 * @param end End of event to check
 * @param repeat Repetition of event (space between starts)
 * @param repeatTill_ Event will not repeat beyond this, value -1 for infinity. Default value is -1
 * @return first time of event specified by given parameters that happens during this class event
 */
time_t RecurringEvent::TimeOfEvent(time_t start, time_t end, time_t repeat, time_t repeatTill_) {
    bool repeatToInfinity_ = (repeatTill_ == -1);
    time_t startA = this->getStartDateUtc();
    time_t startB = start;
    time_t duration = end - start;

    time_t timeDiff = startA - startB;
    while (true) {
        if (startA < startB) {
            startA = getFirstEventTime(startB, this->getStartDateUtc(), this->getDurationUtc(), this->getTimeBetweenEvents());
            if (startB + duration > startA)
                return startA;
        } else {
            startB = getFirstEventTime(startA, start, duration, repeat);
            if (startA + this->getDurationUtc() > startB)
                return startB;
        }

        if (timeDiff == startA - startB)
            break;
        if (!this->isRepeatToInfinity() && this->getRepeatTill() < startA)
            break;
        if (repeatToInfinity_ && repeatTill_ < startB)
            break;
        if (abs(startA - startB) < abs(timeDiff))
            timeDiff = startA - startB;
    }
    return -1;
}

shared_ptr<RecurringItemEvent> RecurringEvent::getSingle(time_t start) {
    if (start % getTimeBetweenEvents() != getStartDateUtc() % getTimeBetweenEvents())
        throw EventNotInRecurringEvent();
    return RecurringItemEvent::getInstance(getTitle(), start, getDurationUtc(), downcasted_shared_from_this<RecurringEvent>());
}

struct mk_shared_RecurringEvent : RecurringEvent {
    mk_shared_RecurringEvent(string title_, time_t startDateUtc_, time_t duration_, time_t timeBetweenEvents_, time_t repeatTill_)
            : RecurringEvent(move(title_), startDateUtc_, duration_, timeBetweenEvents_, repeatTill_) {}

    mk_shared_RecurringEvent(string title_, time_t startDateUtc_, time_t duration_, time_t timeBetweenEvents_)
            : RecurringEvent(move(title_), startDateUtc_, duration_, timeBetweenEvents_) {}
};

shared_ptr<RecurringEvent> RecurringEvent::getInstance(string title_, time_t startDateUtc_, time_t duration_, time_t timeBetweenEvents_, time_t repeatTill_) {
    return make_shared<mk_shared_RecurringEvent>(move(title_), startDateUtc_, duration_, timeBetweenEvents_, repeatTill_);
}

shared_ptr<RecurringEvent> RecurringEvent::getInstance(string title_, time_t startDateUtc_, time_t duration_, time_t timeBetweenEvents_) {
    return make_shared<mk_shared_RecurringEvent>(move(title_), startDateUtc_, duration_, timeBetweenEvents_);
}
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
    if (childNode && childNode->getEndDateUtc() <= end) {
        auto childEvents = childNode->getEvents(start, end);
        result.insert(childEvents.begin(), childEvents.end());
    }
    return result;
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
        return nullptr;
    if (!repeatToInfinity && time + getDurationUtc() > repeatTill) {
        if (childNode)
            return childNode->eventExists(start, end, repeat, repeatTill_);
        return nullptr;
    }
    time = (time - getStartDateUtc()) % getTimeBetweenEvents();
    return getSingle(time);
}


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

shared_ptr<RecurringEvent> RecurringEvent::getParentOfItem(const shared_ptr<RecurringItemEvent> &recurringItem) {
    time_t timediff = recurringItem->getStartDateUtc() - getStartDateUtc();
    if (timediff < 0)
        return nullptr;
    if (recurringItem->getStartDateUtc() < getStartDateUtc()) {
        if (parentNode)
            return parentNode->getParentOfItem(recurringItem);
        return nullptr;
    }

    if (!repeatToInfinity && recurringItem->getEndDateUtc() > getRepeatTill()) {
        if (childNode)
            return childNode->getParentOfItem(recurringItem);
        return nullptr;
    }

    if ((timediff % getTimeBetweenEvents()) == 0)
        return downcasted_shared_from_this<RecurringEvent>();
    return nullptr;
}

shared_ptr<Event> RecurringEvent::freeRecurringItemEvent(const shared_ptr<RecurringItemEvent> &event, Event::actionType actionType) {
    //GET RECURRING EVENT FROM SEQUENCE THAT GENERATES RECURRING ITEM EVENT
    auto owner = getParentOfItem(event);
    if (!owner)
        throw EventNotInRecurringEvent();
    if (owner != shared_from_this())
        return owner->freeRecurringItemEvent(event, actionType);


    //IF ACTION TYPE EFFECTS ENTIRE SEQUENCE
    if (actionType == Event::actionType::AllEvents)
        return freeAllRecurringItemEvent();
    if (actionType == Event::actionType::ThisAndNext)
        return freeThisAndNextRecurringItemEvent(event);
    if (actionType == Event::actionType::OnlyThis)
        return freeOnlyOneRecurringItemEvent(event);

    return nullptr;

}

shared_ptr<RecurringEvent> RecurringEvent::getFirstNode() {
    if (parentNode)
        return parentNode->getFirstNode();
    return downcasted_shared_from_this<RecurringEvent>();
}

bool RecurringEvent::deleteThisNode() {
    if (parentNode) {
        parentNode->childNode = childNode;
        return true;
    } else if (childNode) {
        childNode->parentNode = parentNode;
        *this = *childNode;
        if (childNode) {
            childNode = childNode->childNode;
            childNode->parentNode = downcasted_shared_from_this<RecurringEvent>();
        } else {
            childNode = nullptr;
        }
        return true;
    }
    return false;
}

shared_ptr<Event> RecurringEvent::freeOnlyOneRecurringItemEvent(const shared_ptr<RecurringItemEvent> &event) {
    //RECURRING ITEM EVENT IS THE FIRST IN SEQUENCE
    if (event->getStartDateUtc() == this->getStartDateUtc()) {
        setStartDateUtc(getStartDateUtc() + timeBetweenEvents);
        if (!isValid())
            //IF THIS NODE CANT BE DELETED THEN IT MUST BE THE LAST EVENT OF ENTIRE RANGE - RETURN IT INSTEAD
            if (!deleteThisNode()) {
                setStartDateUtc(event->getStartDateUtc());
                repeatTill = event->getEndDateUtc();
                return shared_from_this();
            }
        return event;
    }
    //RECURRING ITEM EVENT IS LAST IN SEQUENCE
    if (!repeatToInfinity && event->getEndDateUtc() + timeBetweenEvents > repeatTill) {
        setRepeatTill(event->getStartDateUtc());
        return event;
    }
    //RECURRING ITEM EVENT IS IN THE MIDDLE OF THE SEQUENCE
    //COPY THIS SEQUENCE AND SET ITS START TO START OF EVENT + TIME BETWEEN EVENTS
    shared_ptr<RecurringEvent> next = make_shared<RecurringEvent>(RecurringEvent(*this));
    next->setStartDateUtc(event->getStartDateUtc() + timeBetweenEvents);
    next->parentNode = downcasted_shared_from_this<RecurringEvent>();
    childNode = next;
    //SET END OF THIS SEQUENCE TO START OF EVENT
    setRepeatTill(event->getStartDateUtc());
    setRepeatToInfinity(false);
    return event;
}

shared_ptr<Event> RecurringEvent::freeThisAndNextRecurringItemEvent(const shared_ptr<RecurringItemEvent> &event) {
    //RECURRING ITEM EVENT IS THE FIRST IN SEQUENCE
    if (event->getStartDateUtc() == this->getStartDateUtc()) {
        if (parentNode)
            parentNode->childNode = nullptr;
        return shared_from_this();
    }
    //RECURRING ITEM EVENT IS LAST IN SEQUENCE
    //OR
    //RECURRING ITEM EVENT IS IN THE MIDDLE OF THE SEQUENCE
    //SET END OF THIS SEQUENCE TO START OF EVENT
    setRepeatTill(event->getStartDateUtc());
    //COPY THIS SEQUENCE AND SET ITS START TO START OF EVENT
    shared_ptr<RecurringEvent> next = make_shared<RecurringEvent>(RecurringEvent(*this));
    next->setStartDateUtc(event->getStartDateUtc());
    childNode = nullptr;
    return next;
}

shared_ptr<Event> RecurringEvent::freeAllRecurringItemEvent() {
    return getFirstNode();
}

bool RecurringEvent::isValid() {
    return repeatToInfinity || getStartDateUtc() < getRepeatTill();
}
/*
RecurringEvent &RecurringEvent::operator=(const RecurringEvent &event) {
    if (this == &event)
        return *this;

    return *this;
}
*/
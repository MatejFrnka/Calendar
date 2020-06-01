/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 29.04.2020
 */

#include <sstream>
#include "RecurringEvent.h"

RecurringEvent::RecurringEvent(string title_, time_t startDateUtc_, time_t duration_, time_t timeBetweenEvents_, time_t repeatTill_)
        : Event(move(title_), startDateUtc_, duration_) {
    timeBetweenEvents = timeBetweenEvents_;
    repeatTill = repeatTill_;
    repeatToInfinity = false;
}

RecurringEvent::RecurringEvent(string title_, time_t startDateUtc_, time_t duration_, time_t timeBetweenEvents_)
        : Event(move(title_), startDateUtc_, duration_) {
    timeBetweenEvents = timeBetweenEvents_;
    repeatTill = 0;
    repeatToInfinity = true;
}

RecurringEvent::RecurringEvent(const RecurringEvent &event) : Event(event) {
    repeatToInfinity = event.repeatToInfinity;
    repeatTill = event.repeatTill;
    timeBetweenEvents = event.timeBetweenEvents;
    if (event.childNode) {
        shared_ptr<RecurringEvent> child = make_shared<RecurringEvent>(*event.childNode);
        auto wptr = std::shared_ptr<RecurringEvent>(this, [](RecurringEvent *) {});
        child->parentNode = downcasted_shared_from_this<RecurringEvent>();
        childNode = child;
    }
}

EventSet<shared_ptr<SingleEvent>> RecurringEvent::getEvents(time_t start, time_t end) {
    EventSet<shared_ptr<SingleEvent>> result;
    time_t eventTime = getFirstEventTime(start, getStartDateUtc(), getDurationUtc(), getTimeBetweenEvents());

    while ((repeatToInfinity || eventTime < repeatTill) && eventTime < end) {
        result.insert(getSingle(eventTime));
        eventTime += timeBetweenEvents;
    }
    if (childNode) {
        auto childEvents = childNode->getEvents(start, end);
        result.insert(childEvents.begin(), childEvents.end());
    }
    return result;
}

time_t RecurringEvent::getRepeatTill() const {
    return repeatTill;
}

bool RecurringEvent::isRepeatToInfinity() const {
    return repeatToInfinity;
}

time_t RecurringEvent::getTimeBetweenEvents() const {
    return timeBetweenEvents;
}

shared_ptr<SingleEvent> RecurringEvent::eventExists(time_t start, time_t end) {
    auto events = this->getEvents(start, end);
    if (!events.empty())
        return *events.begin();
    return nullptr;
}

shared_ptr<SingleEvent> RecurringEvent::eventExists(time_t start, time_t end, time_t repeat) {
    return eventExists(start, end, repeat, -1);
}

shared_ptr<SingleEvent> RecurringEvent::eventExists(time_t start, time_t end, time_t repeat, time_t repeatTill_) {
    time_t time = TimeOfEvent(start, end, repeat, repeatTill_);
    if (time == -1 || (!repeatToInfinity && repeatTill_ != -1 && time + end - start > repeatTill_))
        return nullptr;
    if (!repeatToInfinity && (time + getDurationUtc() > repeatTill)) {
        if (childNode)
            return childNode->eventExists(start, end, repeat, repeatTill_);
        return nullptr;
    }
    //subtract time difference between this recurring event start and time start so that time start is generated by this recurring event
    time -= (time - getStartDateUtc()) % getTimeBetweenEvents();
    return getSingle(time);
}


time_t RecurringEvent::TimeOfEvent(time_t start, time_t end, time_t repeat, time_t repeatTill_) const {
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
        throw EventNotInRecurringEventException();
    auto firstNode = getFirstNode();
    return RecurringItemEvent::getInstance(firstNode->getTitle(), start, firstNode->getDurationUtc(), firstNode);
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
        if (!parentNode.expired())
            return shared_ptr<RecurringEvent>(parentNode)->getParentOfItem(recurringItem);
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
        throw EventNotInRecurringEventException();
    if (owner != shared_from_this())
        return owner->freeRecurringItemEvent(event, actionType);


    //IF ACTION TYPE EFFECTS ENTIRE SEQUENCE
    if (actionType == Event::actionType::AllEvents)
        return getFirstNode();
    if (actionType == Event::actionType::ThisAndNext)
        return freeThisAndNextRecurringItemEvent(event);
    if (actionType == Event::actionType::OnlyThis)
        return freeOnlyOneRecurringItemEvent(event);
    return nullptr;
}

shared_ptr<RecurringEvent> RecurringEvent::getFirstNode() {
    if (!parentNode.expired())
        return shared_ptr<RecurringEvent>(parentNode)->getFirstNode();
    return downcasted_shared_from_this<RecurringEvent>();
}

bool RecurringEvent::deleteThisNode() {
    if (!parentNode.expired()) {
        shared_ptr<RecurringEvent>(parentNode)->childNode = childNode;
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
    //IF RECURRING ITEM EVENT IS THE FIRST IN SEQUENCE
    if (event->getStartDateUtc() == this->getStartDateUtc()) {
        startDateUtc = getStartDateUtc() + timeBetweenEvents;
        if (!isValid())
            //IF THIS NODE CANT BE DELETED THEN IT MUST BE THE LAST NODE OF ENTIRE RANGE - RETURN IT INSTEAD
            if (!deleteThisNode()) {
                setStartDateUtc(event->getStartDateUtc());
                repeatTill = event->getEndDateUtc();
                return shared_from_this();
            }
        return event;
    }
    //RECURRING ITEM EVENT IS LAST IN SEQUENCE
    if (!repeatToInfinity && event->getEndDateUtc() + timeBetweenEvents > repeatTill) {
        repeatTill = event->getStartDateUtc();
        return event;
    }
    //RECURRING ITEM EVENT IS IN THE MIDDLE OF THE SEQUENCE
    //COPY THIS SEQUENCE AND SET ITS START TO START OF EVENT + TIME BETWEEN EVENTS
    shared_ptr<RecurringEvent> next = make_shared<RecurringEvent>(RecurringEvent(*this));
    next->startDateUtc = event->getStartDateUtc() + timeBetweenEvents;
    next->parentNode = downcasted_shared_from_this<RecurringEvent>();
    childNode = next;
    //SET END OF THIS SEQUENCE TO START OF EVENT
    repeatTill = event->getStartDateUtc();
    repeatToInfinity = false;
    return event;
}

shared_ptr<RecurringEvent> RecurringEvent::freeThisAndNextRecurringItemEvent(const shared_ptr<RecurringItemEvent> &event) {
    //RECURRING ITEM EVENT IS THE FIRST IN SEQUENCE
    if (event->getStartDateUtc() == this->getStartDateUtc()) {
        if (!parentNode.expired())
            shared_ptr<RecurringEvent>(parentNode)->childNode = nullptr;
        return downcasted_shared_from_this<RecurringEvent>();
    }
    //RECURRING ITEM EVENT IS LAST IN SEQUENCE
    //OR
    //RECURRING ITEM EVENT IS IN THE MIDDLE OF THE SEQUENCE
    //SET END OF THIS SEQUENCE TO START OF EVENT
    repeatTill = event->getStartDateUtc();
    repeatToInfinity = false;
    //COPY THIS SEQUENCE AND SET ITS START TO START OF EVENT
    shared_ptr<RecurringEvent> next = make_shared<RecurringEvent>(RecurringEvent(*this));
    next->setStartDateUtc(event->getStartDateUtc());
    childNode = nullptr;
    return next;
}

bool RecurringEvent::isValid() const {
    return repeatToInfinity || getStartDateUtc() < getRepeatTill();
}

shared_ptr<Event> RecurringEvent::freeSelf(Event::actionType actionType) {
    return shared_from_this();
}

string RecurringEvent::infoAll() {
    tm time{};
    time_t start = getStartDateUtc();
    time = *localtime(&start);
    stringstream ss;

    ss << "Title:\t" << getTitle() << '\n'
       << "Type:\tRecurring Event\n"
       << "Start:\t" << asctime(&time);

    time_t end = getEndDateUtc();
    time = *localtime(&end);
    ss << "End:\t" << asctime(&time)
       << "Repeat every:\t" << getTimeBetweenEvents() << "s\n";
    shared_ptr<RecurringEvent> lastEvent = downcasted_shared_from_this<RecurringEvent>();
    while (lastEvent->childNode)
        lastEvent = childNode;
    if (lastEvent->repeatToInfinity)
        ss << "Repeat till: infinity\n";
    else {
        time_t repeatEnd = lastEvent->getRepeatTill();
        time = *localtime(&repeatEnd);
        ss << "Repeat till:\t" << asctime(&time);
    }
    if (editable)
        ss << "Event is editable" << endl;
    else
        ss << "Event is not editable" << endl;
    return ss.str();
}

shared_ptr<Event> RecurringEvent::checkCollision(const EventSet<shared_ptr<Event>> &ev) const {
    for (const auto &event :ev) {
        auto res = event->eventExists(getStartDateUtc(), getEndDateUtc(), getTimeBetweenEvents(), isRepeatToInfinity() ? getRepeatTill() : -1);
        if (res)
            return res;
    }
    if (childNode)
        return childNode->checkCollision(ev);
    return nullptr;
}

shared_ptr<Event> RecurringEvent::getCopy() {
    return make_shared<RecurringEvent>(*this);
}

void RecurringEvent::setStartDateUtc(time_t startDateUtc) {
    time_t timeDiff = startDateUtc - getStartDateUtc();
    Event::setStartDateUtc(startDateUtc);
    if (childNode) {
        childNode->setStartDateUtc(childNode->getStartDateUtc() + timeDiff);
    }
}

void RecurringEvent::setDurationUtc(time_t durationUtc) {
    Event::setDurationUtc(durationUtc);
    if (childNode)
        childNode->setDurationUtc(durationUtc);
}

void RecurringEvent::saveState() {
    state = make_shared<RecurringEvent>(*this);
}

void RecurringEvent::restoreState() {
    *this = *state;
}


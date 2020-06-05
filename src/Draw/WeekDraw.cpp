/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 22.05.2020
 */

#include <iomanip>
#include "WeekDraw.h"
#include "../Utility/DatetimeUtility.h"
#include "../Calendar/SingleEvent.h"

void WeekDraw::drawEvents(tm &time) {
    time_t start = DatetimeUtility::getStartRangeTime(DatetimeUtility::Week, &time);
    int mday = time.tm_mday;
    out << DatetimeUtility::drawDate(time, DatetimeUtility::RangeTime::Week) << endl;
    time_t end = DatetimeUtility::getEndRangeTime(DatetimeUtility::Day, &time);
    tm *eventTime;
    for (int i = 0; i < 7; ++i) {
        out.fill('0');
        auto todayEvents = eventManager.getEvents(start, end);
        out << std::setw(2) << mday << ". " << DatetimeUtility::getWeekDays()[i] << '\t';
        for (const auto &event : todayEvents) {
            // IF EVENT STARTS BEFORE THE DAY DOES
            if (event != *todayEvents.begin())
                out << string(8, ' ');
            if (event->getStartDateUtc() < start)
                out << string(5, '.');
            else {
                time_t t = event->getStartDateUtc();
                eventTime = localtime(&t);
                out << std::setw(2) << eventTime->tm_hour << ':' << std::setw(2) << eventTime->tm_min;
            }
            out << " - ";
            // IF EVENT ENDS AFTER THE DAY DOES
            if (event->getEndDateUtc() > end)
                out << string(5, '.');
            else {
                time_t t = event->getEndDateUtc();
                eventTime = localtime(&t);
                out << std::setw(2) << eventTime->tm_hour << ':' << std::setw(2) << eventTime->tm_min;
            }
            out << ": " << event->getTitle() << std::endl;
        }
        if (todayEvents.empty())
            out << "Empty" << std::endl;
        start = end;
        mday = time.tm_mday;
        end = DatetimeUtility::getEndRangeTime(DatetimeUtility::Day, &time);
    }
    time.tm_mday -= 8;
}

void WeekDraw::moveNext(tm &time) const {
    time.tm_mday += 7;
}

void WeekDraw::movePrevious(tm &time) const {
    time.tm_mday -= 7;
}

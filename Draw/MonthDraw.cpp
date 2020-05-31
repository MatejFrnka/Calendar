/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 22.05.2020
 */

#include <iomanip>
#include "MonthDraw.h"

void MonthDraw::drawEvents(tm &time) {
    time_t startTime = DatetimeUtility::getStartRangeTime(DatetimeUtility::Month, &time);

    int weekDay = DatetimeUtility::convertWeekDay(time.tm_wday);
    int numberOfDays = DatetimeUtility::getNumberOfDays(time.tm_mon, time.tm_year + 1900);

    out << DatetimeUtility::drawDate(time, DatetimeUtility::RangeTime::Month) << endl;
    //Draw week days
    for (const auto &dayOfWeek : DatetimeUtility::getWeekDays()) {
        out << dayOfWeek << '\t';
    }
    out << endl;
    //Draw empty fields
    for (int i = 0; i < weekDay; ++i) {
        out << "\t";
    }
    //Draw days
    for (int i = 1; i <= numberOfDays; ++i) {
        time.tm_mday = i + 1;
        time_t endTime = mktime(&time);
        auto events = eventManager.getEvents(startTime, endTime);
        //highlight day if event happens during it
        if (!events.empty())
            out << "|";
        else
            out << " ";
        //day number
        out << i;
        if (!events.empty())
            out << "|";
        out << "\t";
        //New line after sunday
        if ((i + weekDay) % 7 == 0) {
            out << '\n' << endl;
        }
        startTime = endTime;
    }
    out << endl;
    time.tm_mday -= numberOfDays;
    mktime(&time);
}

void MonthDraw::moveNext(tm &time) const {
    time.tm_mon++;
}

void MonthDraw::movePrevious(tm &time) const {
    time.tm_mon--;
}

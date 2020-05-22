/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 22.05.2020
 */

#include "MonthDraw.h"

void MonthDraw::drawEvents(time_t time) {
    tm *displayTime = localtime(&time);
    time_t startTime = DatetimeUtility::getStartRangeTime(DatetimeUtility::Month, displayTime);

    int weekDay = DatetimeUtility::convertWeekDay(displayTime->tm_wday);
    int numberOfDays = DatetimeUtility::getNumberOfDays(displayTime->tm_mon, displayTime->tm_year + 1900);


    out << DatetimeUtility::getMonths()[displayTime->tm_mon] << "-" << displayTime->tm_year + 1900 << endl;
    //Draw week days
    for (const auto &dayOfWeek : DatetimeUtility::getWeekDays()) {
        out << "\t" << dayOfWeek;
    }
    out << endl;
    //Draw first week number
    out << 0 << ":\t";
    //Draw empty fields
    for (int i = 0; i < weekDay; ++i) {
        out << "\t";
    }
    //Draw days
    for (int i = 1; i <= numberOfDays; ++i) {
        displayTime->tm_mday = i + 1;
        time_t endTime = mktime(displayTime);
        auto events = eventManager.checkAvailability(startTime, endTime);
        //week number
        //highlight day if event happens during it
        if (events)
            out << "|";
        //day number
        out << i;
        if (events)
            out << "|";
        out << "\t";
        //New line after sunday
        if ((i + weekDay) % 7 == 0) {
            out << '\n' << endl;
            //Draw week number
            out << (i / 7) + 1 << ":\t";
        }
        startTime = endTime;
    }
}
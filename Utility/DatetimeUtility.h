/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 19.05.2020
 */

#ifndef CALENDAR_DATETIMEUTILITY_H
#define CALENDAR_DATETIMEUTILITY_H

#include <ctime>
#include <string>
#include <vector>

class DatetimeUtility {
public:
    enum RangeTime {
        Day,
        Week,
        Month
    };

    static time_t getStartRangeTime(RangeTime range, tm *resultTime);

    static time_t getEndRangeTime(RangeTime range, tm *resultTime);

    static int convertWeekDay(int day);

    static int getNumberOfDays(int month, int year);

    static std::vector<std::string> getWeekDays();

    static std::vector<std::string> getMonths();

    static std::string drawDate(const tm &time, RangeTime range);
};


#endif //CALENDAR_DATETIMEUTILITY_H

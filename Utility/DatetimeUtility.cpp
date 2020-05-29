/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 19.05.2020
 */

#include "DatetimeUtility.h"

int DatetimeUtility::getNumberOfDays(int month, int year) {
    if (month == 1) {
        if ((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0))
            return 29;
        else
            return 28;
    } else if (month == 0 || month == 2 || month == 4 || month == 6 || month == 7
               || month == 9 || month == 11)
        return 31;
    else
        return 30;
}

time_t DatetimeUtility::getStartRangeTime(DatetimeUtility::RangeTime range, tm *resultTime) {
    mktime(resultTime);
    int isdst = resultTime->tm_isdst;
    resultTime->tm_sec = 0;
    resultTime->tm_min = 0;
    resultTime->tm_hour = 0;
    if (range == RangeTime::Week) {
        resultTime->tm_mday -= convertWeekDay(resultTime->tm_wday);
    }
    if (range == RangeTime::Month) {
        resultTime->tm_mday = 1;
    }
    time_t result = mktime(resultTime);
    //If daylight saving changes
    if (resultTime->tm_isdst == 0 && isdst == 1) {
        resultTime->tm_hour += 2;
        result = mktime(resultTime);
    }
    return result;
}

time_t DatetimeUtility::getEndRangeTime(DatetimeUtility::RangeTime range, tm *resultTime) {
    resultTime->tm_sec = 60;
    resultTime->tm_min = 59;
    resultTime->tm_hour = 23;
    if (range == RangeTime::Week) {
        resultTime->tm_mday += 7 - resultTime->tm_wday;
    }
    if (range == RangeTime::Month) {
        resultTime->tm_mday = getNumberOfDays(resultTime->tm_mon, resultTime->tm_year);
    }
    return mktime(resultTime);

}

int DatetimeUtility::convertWeekDay(int day) {
    return (day + 6) % 7;
}

std::vector<std::string> DatetimeUtility::getWeekDays() {
    return std::vector<std::string>{"Mo", "Tu", "We", "Th", "Fr", "Sa", "Su"};
}

std::vector<std::string> DatetimeUtility::getMonths() {
    return std::vector<std::string>{"January",
                                    "February",
                                    "March",
                                    "April",
                                    "May",
                                    "June",
                                    "July",
                                    "August",
                                    "September",
                                    "October",
                                    "November",
                                    "December"};
}

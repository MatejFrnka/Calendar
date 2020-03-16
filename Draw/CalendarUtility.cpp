//
// Created by Matej Frnka on 14.03.2020.
//

#include "CalendarUtility.h"

int CalendarUtility::getMonth(time_t *time) {
    tm *tmTime = gmtime(time);
    int result = tmTime->tm_mon;
    delete tmTime;
    return result;
}

int CalendarUtility::getDay(time_t *time) {
    tm *tmTime = gmtime(time);
    int result = tmTime->tm_mday;
    delete tmTime;
    return result;
}

vector<Event *> *CalendarUtility::filterEvents(int day, vector<Event *> *events) {
    vector<Event *> *result = new vector<Event *>();
    for (auto &event : *events) {
        if (event->getDay(true) == day || event->getDay(false) == day)
            result->push_back(event);


    }
    return result;

}

int CalendarUtility::getNumberOfDays(int month, int year) {
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

time_t CalendarUtility::getStartRangeTime(CalendarUtility::RangeTime range,  tm * resultTime) {
    resultTime->tm_sec = 0;
    resultTime->tm_min = 0;
    resultTime->tm_hour = 0;
    if (range == RangeTime::Week) {
        resultTime->tm_mday -= convertWeekDay(resultTime->tm_wday);
    }
    if (range == RangeTime::Month) {
        resultTime->tm_mday = 1;
    }
    return mktime(resultTime) + (timeZone * 3600);

}

time_t CalendarUtility::getEndRangeTime(CalendarUtility::RangeTime range, tm * resultTime) {
    resultTime->tm_sec = 60;
    resultTime->tm_min = 59;
    resultTime->tm_hour = 23;
    if (range == RangeTime::Week) {
        resultTime->tm_mday -= convertWeekDay(resultTime->tm_wday);
    }
    if (range == RangeTime::Month) {
        resultTime->tm_mday = getNumberOfDays(resultTime->tm_mon, resultTime->tm_year);
    }
    return  mktime(resultTime) + (timeZone * 3600);
}

int CalendarUtility::convertWeekDay(int day) {
    return (day + 6) % 7;
}


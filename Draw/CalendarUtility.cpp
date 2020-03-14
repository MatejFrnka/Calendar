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
    }
    else if (month == 0 || month == 2 || month == 4 || month == 6 || month == 7
             || month == 9 || month == 11)
        return 31;
    else
        return 30;
}
/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 29.04.2020
 */


#pragma once

#include <ctime>
#include <vector>
#include "../Calendar/Event.h"

using namespace std;

class CalendarUtility {
public:
    enum RangeTime{
        Day,
        Week,
        Month
    };
    int getMonth(time_t *time);

    int getDay(time_t *time);

    int timeZone = 1;
    time_t getStartRangeTime(RangeTime range,  tm * resultTime);
    time_t getEndRangeTime(RangeTime range,  tm * resultTime);
    int convertWeekDay(int day);
    int getWeekDay(time_t time);
    vector<Event *> *filterEvents(int day, vector<Event *> *events);

    int getNumberOfDays(int month, int year);

    string weekDays[7] = {"Mo", "Tu", "We", "Th", "Fr", "Sa", "Su"};
};
//
// Created by Matej Frnka on 14.03.2020.
//

#ifndef CALENDAR_CALENDARUTILITY_H
#define CALENDAR_CALENDARUTILITY_H

#include "./../ProjectIncludes.h"
#include "./../Calendar/CalendarIncludes.h"

class CalendarUtility {
public:
    int getMonth(time_t *time);

    int getDay(time_t *time);

    vector<Event *> *filterEvents(int day, vector<Event *> *events);

    int getNumberOfDays(int month, int year);

    string weekDays[7] = {"Mo", "Tu", "We", "Th", "Fr", "Sa", "Su"};
};


#endif //CALENDAR_CALENDARUTILITY_H

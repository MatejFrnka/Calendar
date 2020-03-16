//
// Created by Matej Frnka on 13.03.2020.
//

#include "DrawMonth.h"
#include <chrono>

void DrawMonth::draw(EventManager *eventManager, time_t *time) {
    tm *displayTime = gmtime(time);
    time_t startTime = calendarUtility.getStartRangeTime(calendarUtility.Month, displayTime);

    int weekDay = calendarUtility.convertWeekDay(displayTime->tm_wday);
    int numberOfDays = calendarUtility.getNumberOfDays(displayTime->tm_mon, displayTime->tm_year + 1900);

    time_t endTime = calendarUtility.getEndRangeTime(calendarUtility.Month, displayTime);

    vector<Event *> *events = eventManager->getEvents(startTime, endTime);

    //Draw week days
    for (const auto &weekDay : calendarUtility.weekDays) {
        cout << weekDay << "\t";
    }
    cout << endl;
    //Draw empty fields
    for (int i = 0; i < weekDay; ++i) {
        cout << "\t";
    }
    //Draw days
    for (int i = 1; i <= numberOfDays; ++i) {

        vector<Event *> *eventsToday = calendarUtility.filterEvents(i, events);

        if (!eventsToday->empty())
            cout << "-";
        delete eventsToday;
        //New line after sunday
        cout << i << "\t";
        if ((i + weekDay) % 7 == 0)
            cout << endl << endl;
    }


}
//
// Created by Matej Frnka on 13.03.2020.
//

#include "DrawMonth.h"
#include <chrono>

void DrawMonth::draw(EventManager *eventManager, time_t *time) {

    tm *displayTime = gmtime(time);
    displayTime->tm_mday = 1;
    displayTime->tm_hour = 0;
    displayTime->tm_min = 0;
    displayTime->tm_sec = 0;
    time_t startTime = mktime(displayTime);
    int weekDay = (displayTime->tm_wday + 6) % 7;
    int numberOfDays = calendarUtility.getNumberOfDays(displayTime->tm_mon, displayTime->tm_year + 1900);

    displayTime->tm_mday = numberOfDays;
    displayTime->tm_hour = 23;
    displayTime->tm_min = 59;
    displayTime->tm_sec = 60;


    time_t endTime = mktime(displayTime);

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
    for (int i = 1; i <= numberOfDays; ++i) {

        vector<Event *> *eventsToday = calendarUtility.filterEvents(i, events);

        if (!eventsToday->empty())
            cout << "-";
        delete eventsToday;

        cout << i << "\t";
        if ((i+weekDay)%7 == 0)
            cout << endl << endl;
    }


}
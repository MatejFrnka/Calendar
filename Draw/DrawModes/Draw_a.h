//
// Created by Matej Frnka on 13.03.2020.
//

#ifndef CALENDAR_DRAW_A_H
#define CALENDAR_DRAW_A_H

#include "./../../ProjectIncludes.h"
#include "./../../Calendar/CalendarIncludes.h"
#include "../CalendarUtility.h"

class Draw_a {
public:
    virtual void draw(EventManager *eventManager, time_t *time) = 0;

    int dayWidth = 30;
protected:
    CalendarUtility calendarUtility;
};


#endif //CALENDAR_DRAW_A_H

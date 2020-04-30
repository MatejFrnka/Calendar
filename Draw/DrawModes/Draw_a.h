/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 29.04.2020
 */

#pragma once

#include "../../Calendar/EventManager.h"
#include "../CalendarUtility.h"

class Draw_a {
public:
    virtual void draw(EventManager *eventManager, time_t *time) = 0;

    int dayWidth = 30;
protected:
    CalendarUtility calendarUtility;
};

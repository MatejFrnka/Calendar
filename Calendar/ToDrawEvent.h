//
// Created by Matej Frnka on 14.03.2020.
//

#ifndef CALENDAR_TODRAWEVENT_H
#define CALENDAR_TODRAWEVENT_H

#include "../ProjectIncludes.h"
#include "CalendarIncludes.h"

class ToDrawEvent : public Event {
public:
    ToDrawEvent(Event *event);

    Event *originalEvent = nullptr;

    int width = 100;
    int col = 0;
};


#endif //CALENDAR_TODRAWEVENT_H

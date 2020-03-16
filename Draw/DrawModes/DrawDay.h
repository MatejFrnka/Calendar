//
// Created by Matej Frnka on 14.03.2020.
//

#ifndef CALENDAR_DRAWDAY_H
#define CALENDAR_DRAWDAY_H

#include "./../../ProjectIncludes.h"
#include "./../DrawIncludes.h"


class DrawDay : public Draw_a {
public:
    void draw(EventManager *eventManager, time_t *time) override;

private:
    string drawLine(int width);

    enum CalendarType {
        Start,
        Center,
        End
    };

    string drawCalendarBlock(int width, string body, CalendarType type);

    string customFill(int width, string *body, string fillChar, string lborder, string rborder);

    Event *getCurrent(vector<Event *> *events, int hour, int minute);
};


#endif //CALENDAR_DRAWDAY_H

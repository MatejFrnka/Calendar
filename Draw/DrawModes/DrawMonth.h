//
// Created by Matej Frnka on 13.03.2020.
//

#ifndef CALENDAR_DRAWMONTH_H
#define CALENDAR_DRAWMONTH_H


#include "Draw_a.h"

class DrawMonth : public Draw_a {
public:
    void draw(EventManager *eventManager, time_t *time) override;

private:

};


#endif //CALENDAR_DRAWMONTH_H

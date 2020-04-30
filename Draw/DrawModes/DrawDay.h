/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 29.04.2020
 */

#pragma once


#include <ctime>
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include "../../Calendar/Event.h"
#include "../../Calendar/EventManager.h"
#include "Draw_a.h"

using namespace std;

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

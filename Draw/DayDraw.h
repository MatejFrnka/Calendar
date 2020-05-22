/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 10.05.2020
 */

#ifndef CALENDAR_DRAW_DAY_DRAW
#define CALENDAR_DRAW_DAY_DRAW


#include "Draw.h"

class DayDraw : public Draw {
    DayDraw(std::ostream &out_, EventManager &eventManager_) : Draw(out_, eventManager_) {};
};


#endif

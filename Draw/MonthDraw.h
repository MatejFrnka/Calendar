/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 10.05.2020
 */

#ifndef CALENDAR_DRAW_MONTH_DRAW
#define CALENDAR_DRAW_MONTH_DRAW


#include "Draw.h"

class MonthDraw : Draw {
    void drawEvents(EventSet<std::shared_ptr<Event> > events) override;
};


#endif

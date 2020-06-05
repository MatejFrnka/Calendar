/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 10.05.2020
 */

#ifndef CALENDAR_DRAW_WEEK_DRAW
#define CALENDAR_DRAW_WEEK_DRAW


#include "Draw.h"

class WeekDraw : public Draw {
public:
    WeekDraw(std::ostream &out_, EventManager &eventManager_) : Draw(out_, eventManager_) {};

    void moveNext(tm &time) const override;

    void movePrevious(tm &time) const override;

    void drawEvents(tm &time) override;
};


#endif

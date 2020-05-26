/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 10.05.2020
 */

#ifndef CALENDAR_DRAW_MONTH_DRAW
#define CALENDAR_DRAW_MONTH_DRAW


#include "Draw.h"
#include "../Utility/DatetimeUtility.h"

class MonthDraw : public Draw {
public:
    MonthDraw(std::ostream &out_, EventManager &eventManager_) : Draw(out_, eventManager_) {};

    void moveNext(tm &time) override;

    void movePrevious(tm &time) override;

    void drawEvents(tm &time) override;
};

#endif

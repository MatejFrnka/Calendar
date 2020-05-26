/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 10.05.2020
 */

#ifndef CALENDAR_DRAW_DAY_DRAW
#define CALENDAR_DRAW_DAY_DRAW


#include "Draw.h"
#include "../Utility/DatetimeUtility.h"
#include <iomanip>

class DayDraw : public Draw {
public:
    DayDraw(std::ostream &out_, EventManager &eventManager_) : Draw(out_, eventManager_) {};

    void drawEvents(time_t time) override;

private:
    char timeBorder = '|';
    char timeBreak = '-';
    int width = 50;

    void drawLine(ostream &o, int hour);

    void mkTime(ostream &o, int hour, int minute);

    string customFill(const string &body, char fillChar, char lborder, char rborder, int customWidth) const;
};


#endif

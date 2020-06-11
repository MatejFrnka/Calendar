/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 10.05.2020
 */

#pragma once

#include "Draw.h"
#include "../Utility/DatetimeUtility.h"
#include <iomanip>

class DayDraw : public Draw {
public:
    DayDraw(std::ostream &out_, EventManager &eventManager_) : Draw(out_, eventManager_) {};

    void drawEvents(tm &time) override;

    void moveNext(tm &time) const override;

    void movePrevious(tm &time) const override;

private:
    char timeBorder = '|';
    char timeBreak = '-';
    int width = 50;
    int timeJump = 2;

    void drawLine(std::ostream &o, int hour) const;

    void mkTime(std::ostream &o, int hour, int minute) const;

    std::string customFill(const std::string &body, char fillChar, char lborder, char rborder, unsigned int customWidth) const;

    void drawEvent(const Event &event, int hourStart, int minuteStart, int hourEnd, int minuteEnd) const;

    void drawEventStart(const Event &event, int hourStart, int minuteStart) const;

    void drawEventEnd(const Event &event, int hourEnd, int minuteEnd) const;

};



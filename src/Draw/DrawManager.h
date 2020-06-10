/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 22.05.2020
 */

#ifndef CALENDAR_DRAWMANAGER_H
#define CALENDAR_DRAWMANAGER_H

#include "MonthDraw.h"
#include "WeekDraw.h"
#include "DayDraw.h"
#include "../Calendar/EventManager.h"
#include "Draw.h"

class DrawManager {
public:
    DrawManager(EventManager &eventManager_, std::ostream &out_);

    ~DrawManager() {
        delete drawUtility;
    };

    enum DrawMode {
        month,
        week,
        day,
    };

    /**
     * Set drawn time to next time range
     */
    void next();
    /**
     * Set drawn time to previous time range
     */
    void previous();
    /**
     * Sets time to draw
     * @param time to set drawn time to
     */
    void setDate(time_t time);

    /**
     * Sets draw mode
     * @param drawMode new draw mode
     */
    void setMode(DrawMode drawMode);

    /**
     * Draws time range using provided mode at provided time
     */
    void draw();

private:
    Draw *drawUtility;
    EventManager &eventManager;
    std::ostream &out;
    tm time{};
};


#endif //CALENDAR_DRAWMANAGER_H

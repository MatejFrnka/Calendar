/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 22.05.2020
 */

#ifndef CALENDAR_DRAWMANAGER_H
#define CALENDAR_DRAWMANAGER_H


#include "../Calendar/EventManager.h"
#include "Draw.h"

class DrawManager {
public:
    DrawManager(EventManager &eventManager_, std::ostream &out_);

    enum DrawMode {
        month,
        week,
        day,
    };

    void next();

    void previous();

    void setDate(time_t time);

    void setMode(DrawMode drawMode);

    void draw();

    unique_ptr<Draw> drawUtility;
private:
    EventManager &eventManager;
    std::ostream &out;
    time_t time = 86400;
};


#endif //CALENDAR_DRAWMANAGER_H

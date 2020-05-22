/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 06.05.2020
 */

#ifndef CALENDAR_DRAW_DRAW
#define CALENDAR_DRAW_DRAW

#include <ostream>
#include <memory>
#include "../Utility/EventSet.h"
#include "../Calendar/EventManager.h"

class Event;

class Draw {
public:
    Draw(std::ostream &out_, EventManager &eventManager_) : out(out_), eventManager(eventManager_) {};

    /**
     * Draws events
     * @param events events to draw
     */
    virtual void drawEvents(time_t startTime) = 0;

protected:
    std::ostream &out;
    EventManager &eventManager;
};

#endif



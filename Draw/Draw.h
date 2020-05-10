/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 06.05.2020
 */

#ifndef CALENDAR_DRAW_DRAW
#define CALENDAR_DRAW_DRAW

#include <ostream>
#include <memory>
#include "../Utility/EventSet.h"

class Event;

class Draw {
public:
    Draw(std::ostream &out_);
    /**
     * Draws events
     * @param events events to draw
     */
    virtual void drawEvents(EventSet<std::shared_ptr<Event>> events) = 0;

protected:
    std::ostream &out;
};

#endif



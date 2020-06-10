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

class Draw {
public:
    Draw(std::ostream &out_, EventManager &eventManager_) : out(out_), eventManager(eventManager_) {};

    virtual ~Draw() = default;

    /**
     * Set given time to next time range
     * @param time tm to update
     */
    virtual void moveNext(tm &time) const = 0;
    /**
     * Set given time to previous time range
     * @param time tm to update
     */
    virtual void movePrevious(tm &time) const = 0;

    /**
     * Draws events
     * @param events events to draw
     */
    virtual void drawEvents(tm &time) = 0;

protected:
    std::ostream &out;
    EventManager &eventManager;
};

#endif



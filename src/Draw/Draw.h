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

    virtual ~Draw() = default;

    virtual void moveNext(tm &time) const = 0;

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



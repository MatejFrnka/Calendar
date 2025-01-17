/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 03.06.2020
 */

#pragma once
#include "Calendar/EventManager.h"

/**
 * Runs calendar application
 */
class CalendarApp {
public:
    CalendarApp() = default;

    CalendarApp &operator=(const CalendarApp &app) = delete;

    CalendarApp(const CalendarApp &) = delete;

    /**
     * Starts the application
     */
    void start() const;

private:

    /**
     * Saves events to file
     * @param eventManager event manager to load events from
     * @return true if success, else false
     */
    bool save(EventManager &eventManager) const;
};

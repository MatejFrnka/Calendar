/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 03.06.2020
 */

#ifndef CALENDAR_CALENDARAPP_H
#define CALENDAR_CALENDARAPP_H

#include "Calendar/EventManager.h"

class CalendarApp {
public:
    CalendarApp() = default;

    CalendarApp &operator=(const CalendarApp &app) = delete;

    CalendarApp(const CalendarApp &) = delete;

    void start() const;

private:
    bool load(EventManager &eventManager) const;

    bool save(EventManager &eventManager) const;

};


#endif //CALENDAR_CALENDARAPP_H

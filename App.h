/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 03.06.2020
 */

#ifndef CALENDAR_APP_H
#define CALENDAR_APP_H

#include "Calendar/EventManager.h"

class App {
public:
    App() = default;

    App &operator=(const App &app) = delete;

    App(const App &) = delete;

    void start() const;

private:
    bool load(EventManager &eventManager) const;

    bool save(EventManager &eventManager) const;

};


#endif //CALENDAR_APP_H

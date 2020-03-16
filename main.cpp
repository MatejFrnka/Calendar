#include "ProjectIncludes.h"
#include "Calendar/CalendarIncludes.h"
#include "Draw/DrawIncludes.h"

int main() {

    DrawManager *drawManager = new DrawManager(new DrawMonth());

    EventManager *eventManager = new EventManager();
    auto events = eventManager->getEvents(0, 1000000);
    eventManager->addEvent(new SingleEvent("Pepa", 1583859600, 1583899200));


    eventManager->addEvent(new SingleEvent("Pepa", 1583859600, 1583899200));
    eventManager->addEvent(new SingleEvent("Karel", 1584140400, 1584140500));
    eventManager->addEvent(new RecurringEvent("Reccuring", 1583668800, 1583668900, 604800, 1585440000));
    delete events;

    drawManager->draw(eventManager);

    delete eventManager;
    delete drawManager;

    return 0;
}

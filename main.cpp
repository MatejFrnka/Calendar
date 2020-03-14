#include "ProjectIncludes.h"
#include "Calendar/CalendarIncludes.h"
#include "Draw/DrawIncludes.h"

#include <conio.h>

int main() {
    
    DrawManager *drawManager = new DrawManager(new DrawMonth());
    vector<Event *> *data = new vector<Event *>();
    tm *date = new tm();
    date->tm_year = 2020 - 1900;
    date->tm_mon = 2;
    date->tm_mday = 14;
    time_t start = mktime(date);

    EventManager *e = new EventManager();
    e->addEvent(new SingleEvent("Pepa", 1583859600, 1583899200));
    e->addEvent(new SingleEvent("Karel", 1584140400, 1584140500));
    RecurringEvent *eventos = new RecurringEvent("Reccuring", 1583668800, 1583668900, 604800, 1585440000);
    e->addEvent(eventos);

    vector<Event *> *a = e->getEvents(1583668800, 1585440000);
    RecurringItemEvent *toEdit = dynamic_cast<RecurringItemEvent *>((*a)[3]);
    SingleEvent *editThis = e->editThisOnly(toEdit);
    editThis->title = "loool";

    vector<Event *> *events = e->getEvents(1583017200, 1585695600);
    for (auto &event : *events) {
        cout << event->title << endl;
    }
    //drawManager->draw(e);

}

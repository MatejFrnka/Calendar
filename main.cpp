#include "ProjectIncludes.h"
#include "./Calendar/EventManager.h"

int main() {

    EventManager eventManager;
    SingleEvent event("test", 1580256000, 1580272200);

    eventManager.addEvent(&event);
    SingleEvent event2("test 2", 1580256000, 1580272100);
    eventManager.addEvent(&event2);

    vector<Event *> a = eventManager.getEvents(1580256000, 1580272201);
    for (Event *&it : a) {
        cout << it->title << endl;
    }
    return 0;
}

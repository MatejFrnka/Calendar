#include "ProjectIncludes.h"
#include "./Calendar/EventManager.h"
#include "./Calendar/Event.h"
#include "./Calendar/RecurringEvent.h"

int main() {

    RecurringEvent event("Title", 1000, 1100, 1000);

    vector<Event*> events = event.getEvents(8000, 16000);

    for (auto &item : events){
        cout << item->startDateUtc << endl;
    }


    return 0;
}

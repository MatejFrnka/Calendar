#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <assert.h>
#include <set>
#include <memory>
#include "Calendar/EventManager.h"
#include "./Utility/EventSet.h"

using namespace std;

string drawEvents(const EventSet<shared_ptr<Event>> &s) {
    stringstream ss;
    for (auto event : s) {
        ss << event->getTitle() << " " << event->getStartDateUtc() << " " << event->getEndDateUtc() << endl;
    }
    return ss.str();
}

int main() {

    //EVENT EXISTS TEST
    {

        auto ev = SingleEvent::getInstance("event", 160, 30);
        assert(ev->eventExists(0, 10) == nullptr);

        assert(ev->eventExists(160, 170) != nullptr);
        assert(ev->eventExists(150, 160) == nullptr);
        assert(ev->eventExists(150, 200) != nullptr);
        assert(ev->eventExists(170, 200) != nullptr);
        assert(ev->eventExists(170, 180) != nullptr);
        assert(ev->eventExists(190, 200) == nullptr);

        assert(ev->eventExists(190, 200, 20) == nullptr);
        assert(ev->eventExists(189, 200, 5060) != nullptr);
        assert(ev->eventExists(200, 210, 10) == nullptr);
        assert(ev->eventExists(170, 180, 100) != nullptr);
        assert(ev->eventExists(0, 10, 10) != nullptr);
        assert(ev->eventExists(0, 10, 100) == nullptr);
        assert(ev->eventExists(70, 80, 100) != nullptr);
        assert(ev->eventExists(10, 20, 20) != nullptr);
        assert(ev->eventExists(150, 160, 30) != nullptr);
        assert(ev->eventExists(150, 160, 40) == nullptr);
        assert(ev->eventExists(0, 160, 190) == nullptr);
        assert(ev->eventExists(0, 10, 1000) == nullptr);
        assert(ev->eventExists(150, 200, 500) != nullptr);

        assert(ev->eventExists(150, 160, 40, 700) == nullptr);
        assert(ev->eventExists(150, 160, 30, 700) != nullptr);
        assert(ev->eventExists(10, 20, 20, 170) == nullptr);
        assert(ev->eventExists(0, 10, 10, 50) == nullptr);
        assert(ev->eventExists(150, 200, 10, 50) == nullptr);
        assert(ev->eventExists(0, 10, 20, 190) != nullptr);
        assert(ev->eventExists(0, 10, 20, 180) != nullptr);
        assert(ev->eventExists(160, 170, 20, 160) == nullptr);
        assert(ev->eventExists(70, 80, 50, 170) == nullptr);
        assert(ev->eventExists(70, 80, 50, 180) != nullptr);
        assert(ev->eventExists(360, 370, 50, 700) == nullptr);

        auto ev1 = SingleEvent::getInstance("event", 0, 50);

        assert(ev1->eventExists(50, 60, 60) == nullptr);
        assert(ev1->eventExists(0, 10) != nullptr);
        assert(ev1->eventExists(50, 60) == nullptr);
        assert(ev1->eventExists(0, 10, 20) != nullptr);
    }
    //RECURRING EVENT ITEM EXISTS TEST
    {
        auto ev = RecurringItemEvent::getInstance("event", 160, 30, nullptr);
        assert(ev->eventExists(0, 10) == nullptr);
        assert(ev->eventExists(160, 170) != nullptr);
        assert(ev->eventExists(150, 160) == nullptr);
        assert(ev->eventExists(150, 200) != nullptr);
        assert(ev->eventExists(170, 200) != nullptr);
        assert(ev->eventExists(170, 180) != nullptr);
        assert(ev->eventExists(190, 200) == nullptr);


        assert(ev->eventExists(190, 200, 20) == nullptr);
        assert(ev->eventExists(189, 200, 5060) != nullptr);
        assert(ev->eventExists(200, 210, 10) == nullptr);
        assert(ev->eventExists(170, 180, 100) != nullptr);
        assert(ev->eventExists(0, 10, 10) != nullptr);
        assert(ev->eventExists(0, 10, 100) == nullptr);
        assert(ev->eventExists(70, 80, 100) != nullptr);
        assert(ev->eventExists(10, 20, 20) != nullptr);
        assert(ev->eventExists(150, 160, 30) != nullptr);
        assert(ev->eventExists(150, 160, 40) == nullptr);
        assert(ev->eventExists(0, 160, 190) == nullptr);
        assert(ev->eventExists(0, 10, 1000) == nullptr);
        assert(ev->eventExists(150, 200, 500) != nullptr);

        assert(ev->eventExists(150, 160, 40, 700) == nullptr);
        assert(ev->eventExists(150, 160, 30, 700) != nullptr);
        assert(ev->eventExists(10, 20, 20, 170) == nullptr);
        assert(ev->eventExists(0, 10, 10, 50) == nullptr);
        assert(ev->eventExists(150, 200, 10, 50) == nullptr);
        assert(ev->eventExists(0, 10, 20, 190) != nullptr);
        assert(ev->eventExists(0, 10, 20, 180) != nullptr);
        assert(ev->eventExists(160, 170, 20, 160) == nullptr);
        assert(ev->eventExists(70, 80, 50, 170) == nullptr);
        assert(ev->eventExists(70, 80, 50, 180) != nullptr);
        assert(ev->eventExists(360, 370, 50, 700) == nullptr);


        auto ev1 = RecurringItemEvent::getInstance("event", 0, 50, nullptr);

        assert(ev1->eventExists(50, 60, 60) == nullptr);
        assert(ev1->eventExists(0, 10) != nullptr);
        assert(ev1->eventExists(50, 60) == nullptr);
        assert(ev1->eventExists(0, 10, 20) != nullptr);

    }
    //RECURRING EVENT EXISTS TEST
    {
        auto rev = RecurringEvent::getInstance("event", 150, 50, 100);
        assert(rev->eventExists(0, 10) == nullptr);
        assert(rev->eventExists(0, 50) == nullptr);
        assert(rev->eventExists(100, 150) == nullptr);
        assert(rev->eventExists(200, 210) == nullptr);
        assert(rev->eventExists(50, 100) == nullptr);
        assert(rev->eventExists(100, 151) != nullptr);
        assert(rev->eventExists(155, 160) != nullptr);
        assert(rev->eventExists(1055, 1100) != nullptr);
        assert(rev->eventExists(0, 5000) != nullptr);

        assert(rev->eventExists(100, 150, 100) == nullptr);
        assert(rev->eventExists(200, 250, 100) == nullptr);
        assert(rev->eventExists(100, 150, 200) == nullptr);
        assert(rev->eventExists(150, 50, 100) != nullptr);
        assert(rev->eventExists(25, 50, 50) != nullptr);
        //TODO: ADD MORE UNIT TESTS

        auto rev2 = RecurringEvent::getInstance("event", 150, 50, 100, 500);
        assert(rev2->eventExists(500, 5000) == nullptr);
        assert(RecurringEvent::getInstance("r1", 0, 10, 50, 300)->eventExists(0, 20));
        assert(RecurringEvent::getInstance("r1", 0, 10, 50, 300)->eventExists(30, 60));
        assert(RecurringEvent::getInstance("r1", 0, 10, 50, 300)->eventExists(100, 200));

    }
    //SINGLE EVENT EVENT MANAGER CHECK

    {

        EventManager e1;
        auto ev1 = SingleEvent::getInstance("1", 10, 10);
        auto ev3 = SingleEvent::getInstance("3", 100, 100);
        auto ev2 = SingleEvent::getInstance("2", 30, 30);

        assert(e1.addEvent(ev3));
        assert(e1.addEvent(ev1));
        assert(e1.addEvent(ev2));
        assert(drawEvents(e1.getEvents(0, 300)) == "1 10 20\n"
                                                   "2 30 60\n"
                                                   "3 100 200\n");
        assert(drawEvents(e1.getEvents(10, 200)) == "1 10 20\n"
                                                    "2 30 60\n"
                                                    "3 100 200\n");
        assert(drawEvents(e1.getEvents(15, 150)) == "1 10 20\n"
                                                    "2 30 60\n"
                                                    "3 100 200\n");
        string s = drawEvents(e1.getEvents(120, 130));
        assert(drawEvents(e1.getEvents(120, 130)) == "3 100 200\n");
        assert(drawEvents(e1.getEvents(20, 150)) == "2 30 60\n"
                                                    "3 100 200\n");

        assert(drawEvents(e1.getEvents(30, 60)) == "2 30 60\n");
        assert(drawEvents(e1.getEvents(0, 10)).empty());
        assert(drawEvents(e1.getEvents(20, 30)).empty());
        assert(drawEvents(e1.getEvents(300, 60000654)).empty());
    }
    //RECURRING EVENTS 1
    {
        EventManager e1;

        e1.addEvent(RecurringEvent::getInstance("1", 10, 10, 100, 1010));
        assert(drawEvents(e1.getEvents(550, 800)) == "1 610 620\n"
                                                     "1 710 720\n");
        assert(drawEvents(e1.getEvents(1000, 3000)).empty());
        assert(drawEvents(e1.getEvents(0, 15)) == "1 10 20\n");
        assert(drawEvents(e1.getEvents(14, 15)) == "1 10 20\n");
        assert(drawEvents(e1.getEvents(14, 110)) == "1 10 20\n");
        assert(drawEvents(e1.getEvents(0, 30)) == "1 10 20\n");
        assert(drawEvents(e1.getEvents(5000, 10000)) == "");
    }
    //RECURRING EVENTS 2
    {
        EventManager e1;
        EventManager e2;

        auto rev1 = RecurringEvent::getInstance("1", 0, 10, 50);
        auto rev2 = RecurringEvent::getInstance("2", 20, 10, 50, 300);
        auto rev3 = RecurringEvent::getInstance("3", 240, 10, 50, 1000);
        auto rev4 = RecurringEvent::getInstance("4", 2110, 10, 50, 3000);

        assert(e1.addEvent(rev1));
        assert(e1.addEvent(rev4));
        assert(e1.addEvent(rev3));
        assert(e1.addEvent(rev2));

        assert(e2.addEvent(rev4));

        assert(drawEvents(e1.getEvents(0, 150)) == "1 0 10\n"
                                                   "2 20 30\n"
                                                   "1 50 60\n"
                                                   "2 70 80\n"
                                                   "1 100 110\n"
                                                   "2 120 130\n");
        assert(drawEvents(e1.getEvents(0, 5)) == "1 0 10\n");
        assert(drawEvents(e1.getEvents(5, 7)) == "1 0 10\n");

        cout << drawEvents(e2.getEvents(0, 1000));

    }
    //EVENT MANAGER
    {
        EventManager e1;

        assert(e1.addEvent(SingleEvent::getInstance("1", 0, 20)));
        assert(e1.addEvent(SingleEvent::getInstance("2", 30, 60)));
        assert(e1.addEvent(SingleEvent::getInstance("3", 100, 200)));
        assert(e1.addEvent(RecurringEvent::getInstance("r1", 300, 10, 50, 600)));
        assert(!e1.addEvent(RecurringEvent::getInstance("r1", 0, 10, 50, 300)));
        assert(drawEvents(e1.getEvents(30, 31)) == "2 30 90\n");
        assert(!e1.addEvent(SingleEvent::getInstance("2", 30, 31)));
        assert(drawEvents(e1.getEvents(29, 30)).empty());
        assert(e1.addEvent(SingleEvent::getInstance("2", 29, 1)));

        assert(drawEvents(e1.getEvents(1583859600, 1584223199)).empty());
    }
    cout << "end" << endl;
    return 0;
}

#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <cassert>
#include <memory>
#include "Calendar/EventManager.h"
#include "App/Interface.h"


using namespace std;

string drawEvents(const EventSet<shared_ptr<SingleEvent>> &s) {
    stringstream ss;
    for (const auto &event : s) {
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
        assert(rev->eventExists(150, 200, 100) != nullptr);
        assert(rev->eventExists(25, 50, 50) != nullptr);

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
    //EVENT MANAGER DELETING SINGLE EVENTS
    {
        EventManager e1;
        auto ev1 = SingleEvent::getInstance("1", 50, 10);
        auto ev5 = SingleEvent::getInstance("5", 200, 30);
        auto ev2 = SingleEvent::getInstance("2", 170, 10);
        auto ev3 = SingleEvent::getInstance("3", 180, 1);
        auto ev4 = SingleEvent::getInstance("4", 181, 10);
        assert(e1.addEvent(ev1));
        assert(e1.addEvent(ev2));
        assert(e1.addEvent(ev3));
        assert(!e1.addEvent(ev3));
        assert(e1.addEvent(ev4));
        assert(e1.addEvent(ev5));

        assert(drawEvents(e1.getEvents(0, 300)) == "1 50 60\n"
                                                   "2 170 180\n"
                                                   "3 180 181\n"
                                                   "4 181 191\n"
                                                   "5 200 230\n");
        assert(drawEvents(e1.getEvents(180, 181)) == "3 180 181\n");
        assert(drawEvents(e1.getEvents(180, 182)) == "3 180 181\n"
                                                     "4 181 191\n");
        e1.removeEvent(ev3);
        assert(drawEvents(e1.getEvents(0, 300)) == "1 50 60\n"
                                                   "2 170 180\n"
                                                   "4 181 191\n"
                                                   "5 200 230\n");
        assert(e1.addEvent(ev3));
        assert(drawEvents(e1.getEvents(0, 300)) == "1 50 60\n"
                                                   "2 170 180\n"
                                                   "3 180 181\n"
                                                   "4 181 191\n"
                                                   "5 200 230\n");
        e1.removeEvent(SingleEvent::getInstance("test", 40, 5));
        assert(drawEvents(e1.getEvents(0, 300)) == "1 50 60\n"
                                                   "2 170 180\n"
                                                   "3 180 181\n"
                                                   "4 181 191\n"
                                                   "5 200 230\n");
        e1.removeEvent(ev1);
        e1.removeEvent(ev2);
        e1.removeEvent(ev3);
        e1.removeEvent(ev4);
        e1.removeEvent(ev5);
        assert(drawEvents(e1.getEvents(0, 300)).empty());
    }

    //EVENT MANAGER DELETING RECURRING EVENTS
    {
        EventManager em;
        assert(em.addEvent(RecurringEvent::getInstance("event", 100, 50, 100)));
        assert(drawEvents(em.getEvents(0, 500)) == "event 100 150\n"
                                                   "event 200 250\n"
                                                   "event 300 350\n"
                                                   "event 400 450\n");

        auto evi1 = *em.getEvents(300, 350).begin();

        em.removeEvent(evi1, Event::actionType::OnlyThis);
        assert(drawEvents(em.getEvents(0, 500)) == "event 100 150\n"
                                                   "event 200 250\n"
                                                   "event 400 450\n");
        auto evi2 = *em.getEvents(100, 150).begin();
        em.removeEvent(evi2);
        assert(drawEvents(em.getEvents(0, 500)) == "event 200 250\n"
                                                   "event 400 450\n");
        auto evi3 = *em.getEvents(200, 250).begin();
        em.removeEvent(evi3);
        assert(drawEvents(em.getEvents(0, 500)) == "event 400 450\n");
        auto evi4 = *em.getEvents(6000, 7000).begin();
        em.removeEvent(SingleEvent::getInstance("test", 400, 50));
        assert(drawEvents(em.getEvents(0, 500)) == "event 400 450\n");
        em.removeEvent(evi4, Event::actionType::AllEvents);
        assert(drawEvents(em.getEvents(0, 500000)) == "");

        em.addEvent(RecurringEvent::getInstance("title", 100, 50, 100, 1000));
        assert(drawEvents(em.getEvents(0, 2000)) == "title 100 150\n"
                                                    "title 200 250\n"
                                                    "title 300 350\n"
                                                    "title 400 450\n"
                                                    "title 500 550\n"
                                                    "title 600 650\n"
                                                    "title 700 750\n"
                                                    "title 800 850\n"
                                                    "title 900 950\n");
        em.removeEvent(*em.getEvents(700, 750).begin(), Event::actionType::OnlyThis);
        assert(drawEvents(em.getEvents(0, 2000)) == "title 100 150\n"
                                                    "title 200 250\n"
                                                    "title 300 350\n"
                                                    "title 400 450\n"
                                                    "title 500 550\n"
                                                    "title 600 650\n"
                                                    "title 800 850\n"
                                                    "title 900 950\n");
        em.removeEvent(*em.getEvents(500, 550).begin(), Event::actionType::ThisAndNext);
        assert(drawEvents(em.getEvents(0, 2000)) == "title 100 150\n"
                                                    "title 200 250\n"
                                                    "title 300 350\n"
                                                    "title 400 450\n");
        assert(em.addEvent(SingleEvent::getInstance("title", 500, 500)));
        assert(drawEvents(em.getEvents(0, 2000)) == "title 100 150\n"
                                                    "title 200 250\n"
                                                    "title 300 350\n"
                                                    "title 400 450\n"
                                                    "title 500 1000\n");
        em.removeEvent(*em.getEvents(200, 250).begin(), Event::actionType::OnlyThis);
        assert(drawEvents(em.getEvents(0, 2000)) == "title 100 150\n"
                                                    "title 300 350\n"
                                                    "title 400 450\n"
                                                    "title 500 1000\n");

        auto evi5 = *em.getEvents(300, 350).begin();
        em.removeEvent(evi5, Event::actionType::ThisAndNext);
        assert(drawEvents(em.getEvents(0, 2000)) == "title 100 150\n"
                                                    "title 500 1000\n");
        em.removeEvent(*em.getEvents(100, 150).begin(), Event::actionType::OnlyThis);
        assert(drawEvents(em.getEvents(0, 2000)) == "title 500 1000\n");
        em.removeEvent(*em.getEvents(0, 2000).begin(), Event::actionType::AllEvents);
        assert(drawEvents(em.getEvents(0, 2000)).empty());
        assert(em.addEvent(RecurringEvent::getInstance("title", 500, 50, 100, 550)));
        assert(drawEvents(em.getEvents(0, 2000)) == "title 500 550\n");
        em.removeEvent(*em.getEvents(0, 2000).begin(), Event::AllEvents);
        assert(drawEvents(em.getEvents(0, 2000)).empty());
        assert(em.addEvent(RecurringEvent::getInstance("title", 500, 50, 100, 550)));
        assert(drawEvents(em.getEvents(0, 2000)) == "title 500 550\n");
        em.removeEvent(*em.getEvents(0, 2000).begin(), Event::ThisAndNext);
        assert(drawEvents(em.getEvents(0, 2000)).empty());
        assert(em.addEvent(RecurringEvent::getInstance("title", 500, 50, 100, 750)));
        em.removeEvent(*em.getEvents(600, 2000).begin(), Event::OnlyThis);
        assert(drawEvents(em.getEvents(0, 2000)) == "title 500 550\n"
                                                    "title 700 750\n");
        em.removeEvent(*em.getEvents(400, 2000).begin(), Event::AllEvents);
        assert(drawEvents(em.getEvents(0, 2000)).empty());

        assert(em.addEvent(RecurringEvent::getInstance("title", 500, 50, 100, 750)));
        em.removeEvent(*em.getEvents(600, 2000).begin(), Event::OnlyThis);
        assert(drawEvents(em.getEvents(0, 2000)) == "title 500 550\n"
                                                    "title 700 750\n");
        em.removeEvent(*em.getEvents(400, 2000).begin(), Event::ThisAndNext);
        assert(drawEvents(em.getEvents(0, 2000)).empty());

        assert(em.addEvent(RecurringEvent::getInstance("title", 500, 50, 100, 750)));
        em.removeEvent(*em.getEvents(600, 2000).begin(), Event::OnlyThis);
        assert(drawEvents(em.getEvents(0, 2000)) == "title 500 550\n"
                                                    "title 700 750\n");
        em.removeEvent(*em.getEvents(400, 2000).begin(), Event::OnlyThis);
        em.removeEvent(*em.getEvents(400, 2000).begin(), Event::OnlyThis);
        assert(drawEvents(em.getEvents(0, 2000)).empty());

        em.addEvent(RecurringEvent::getInstance("title", 100, 50, 100, 1000));
        em.removeEvent(*em.getEvents(300, 350).begin(), Event::OnlyThis);
        assert(drawEvents(em.getEvents(0, 2000)) == "title 100 150\n"
                                                    "title 200 250\n"
                                                    "title 400 450\n"
                                                    "title 500 550\n"
                                                    "title 600 650\n"
                                                    "title 700 750\n"
                                                    "title 800 850\n"
                                                    "title 900 950\n");
        assert(em.addEvent(SingleEvent::getInstance("single", 300, 50)));
        assert(drawEvents(em.getEvents(0, 2000)) == "title 100 150\n"
                                                    "title 200 250\n"
                                                    "single 300 350\n"
                                                    "title 400 450\n"
                                                    "title 500 550\n"
                                                    "title 600 650\n"
                                                    "title 700 750\n"
                                                    "title 800 850\n"
                                                    "title 900 950\n");
        em.removeEvent(*em.getEvents(300, 450).begin(), Event::OnlyThis);
        em.removeEvent(*em.getEvents(300, 450).begin(), Event::OnlyThis);
        assert(drawEvents(em.getEvents(0, 2000)) == "title 100 150\n"
                                                    "title 200 250\n"
                                                    "title 500 550\n"
                                                    "title 600 650\n"
                                                    "title 700 750\n"
                                                    "title 800 850\n"
                                                    "title 900 950\n");
        assert(em.addEvent(RecurringEvent::getInstance("r", 300, 50, 1000)));
        assert(drawEvents(em.getEvents(0, 2000)) == "title 100 150\n"
                                                    "title 200 250\n"
                                                    "r 300 350\n"
                                                    "title 500 550\n"
                                                    "title 600 650\n"
                                                    "title 700 750\n"
                                                    "title 800 850\n"
                                                    "title 900 950\n"
                                                    "r 1300 1350\n");
    }
    //FIND FREE SPACE

    {
        EventManager em;
        assert(em.addEvent(RecurringEvent::getInstance("r1", 0, 50, 100)));
        em.removeEvent(*em.getEvents(300, 400).begin());
        assert(em.findFreeSpace(100, 100) == 250);
        em.removeEvent(*em.getEvents(0, 400).begin(), Event::actionType::AllEvents);
        assert(drawEvents(em.getEvents(0, 1000)).empty());
        assert(em.addEvent(SingleEvent::getInstance("t", 200, 100)));
        assert(em.addEvent(SingleEvent::getInstance("t", 301, 100)));
        assert(em.findFreeSpace(200, 1) == 300);
        assert(em.addEvent(SingleEvent::getInstance("t", 300, 1)));
        assert(em.findFreeSpace(200, 1) == 401);
        assert(em.findFreeSpace(100, 1) == 100);
        assert(em.addEvent(RecurringEvent::getInstance("t", 500, 100, 200)));
        assert(em.findFreeSpace(600, 500) == -1);
        assert(em.findFreeSpace(557, 100) == 600);
        assert(em.findFreeSpace(557, 101) == -1);
        auto a = dynamic_pointer_cast<SingleEvent>(*em.getEvents(700, 800).begin());
        assert(em.moveEvent(a, 750));
        assert(drawEvents(em.getEvents(600, 1000)) == "t 750 850\n"
                                                      "t 900 1000\n");
        a = dynamic_pointer_cast<SingleEvent>(*em.getEvents(750, 850).begin());
        assert(em.checkAvailability(801, 901) != nullptr);
        assert(!em.moveEvent(a, 801));
        assert(em.moveEvent(a, 800));
        assert(drawEvents(em.getEvents(600, 1000)) == "t 800 900\n"
                                                      "t 900 1000\n");
        assert(em.moveEvent(a, 600));
        assert(drawEvents(em.getEvents(600, 1000)) == "t 600 700\n"
                                                      "t 900 1000\n");
    }
/*
    {
        EventManager ev;
        ev.addEvent(SingleEvent::getInstance("nazdaaaar karle", 140400, 7980));
        ev.addEvent(SingleEvent::getInstance("this event has a very very very long name", 87000, 960));
        ev.addEvent(SingleEvent::getInstance("Meeting person c", 88380, 1000));
        ev.addEvent(SingleEvent::getInstance("this event starts before the day", 82380, 960));
        ev.addEvent(SingleEvent::getInstance("this event ends after the day", 168360, 960 * 2));
        ev.addEvent(SingleEvent::getInstance("long event", 108000, 3600 * 6));

        cout << "asserts ok" << endl;
        istringstream in("draw week\ndraw set 02-01-1970");
        Interface i(in, cout, ev);
        i.start();

    }
*/

    {
        EventManager ev;
        ev.addEvent(SingleEvent::getInstance("c", 140400, 7980));
        ev.addEvent(SingleEvent::getInstance("this event has a very very very long name", 87000, 960));
        ev.addEvent(SingleEvent::getInstance("c", 88380, 1000));
        ev.addEvent(SingleEvent::getInstance("this event starts before the day", 82380, 960));
        ev.addEvent(SingleEvent::getInstance("this event ends after the day", 168360, 960 * 2));
        ev.addEvent(SingleEvent::getInstance("a", 1590562800, 3600 * 6));
        ev.addEvent(SingleEvent::getInstance("b", 1590361200, 3600 * 6));
        ev.addEvent(SingleEvent::getInstance("c", 1590706800, 100000));
        ev.addEvent(SingleEvent::getInstance("d", 1590447600, 3600 * 6));
        ev.addEvent(SingleEvent::getInstance("e", 1590667200, 3600 * 6));
        ev.addEvent(SingleEvent::getInstance("f", 108000, 3600 * 6));
        ev.addEvent(SingleEvent::getInstance("f", 1590505200, 3600 * 8));


        cout << "asserts ok" << endl;
        istringstream in("draw week");
        Interface i(cin, cout, ev);
        i.start();
    }

    cout << "end" << endl;

    return 0;
}

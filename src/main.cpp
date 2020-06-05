#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <cassert>
#include <memory>
#include "Calendar/EventManager.h"
#include "App/Interface.h"
#include "Utility/Exceptions/EventNotEditableException.h"
#include "Calendar/Event.h"
#include "Calendar/SingleEvent.h"
#include "Calendar/RecurringEvent.h"
#include "Utility/FileUtility.h"
#include "CalendarApp.h"

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

        auto ev = make_shared<SingleEvent>("event", 160, 30);
        assert(ev->eventExists(0, 10) == nullptr);
        assert(ev->eventExists(160, 161) != nullptr);


        assert(ev->eventExists(160, 170) != nullptr);
        assert(ev->eventExists(150, 160) == nullptr);
        assert(ev->eventExists(150, 200) != nullptr);
        assert(ev->eventExists(170, 200) != nullptr);
        assert(ev->eventExists(170, 180) != nullptr);
        assert(ev->eventExists(190, 200) == nullptr);

        assert(ev->eventExists(190, 200, 20, -1) == nullptr);
        assert(ev->eventExists(189, 200, 5060, -1) != nullptr);
        assert(ev->eventExists(200, 210, 10, -1) == nullptr);
        assert(ev->eventExists(170, 180, 100, -1) != nullptr);
        assert(ev->eventExists(0, 10, 10, -1) != nullptr);
        assert(ev->eventExists(0, 10, 100, -1) == nullptr);
        assert(ev->eventExists(70, 80, 100, -1) != nullptr);
        assert(ev->eventExists(10, 20, 20, -1) != nullptr);
        assert(ev->eventExists(150, 160, 30, -1) != nullptr);
        assert(ev->eventExists(150, 160, 40, -1) == nullptr);
        assert(ev->eventExists(0, 160, 190, -1) == nullptr);
        assert(ev->eventExists(0, 10, 1000, -1) == nullptr);
        assert(ev->eventExists(150, 200, 500, -1) != nullptr);

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

        auto ev1 = make_shared<SingleEvent>("event", 0, 50);

        assert(ev1->eventExists(50, 60, 60, -1) == nullptr);
        assert(ev1->eventExists(0, 10) != nullptr);
        assert(ev1->eventExists(50, 60) == nullptr);
        assert(ev1->eventExists(0, 10, 20, -1) != nullptr);
    }
    //RECURRING EVENT ITEM EXISTS TEST
    {
        auto ev = make_shared<RecurringItemEvent>("event", 160, 30, nullptr);
        assert(ev->eventExists(0, 10) == nullptr);
        assert(ev->eventExists(160, 170) != nullptr);
        assert(ev->eventExists(150, 160) == nullptr);
        assert(ev->eventExists(150, 200) != nullptr);
        assert(ev->eventExists(170, 200) != nullptr);
        assert(ev->eventExists(170, 180) != nullptr);
        assert(ev->eventExists(190, 200) == nullptr);


        assert(ev->eventExists(190, 200, 20, -1) == nullptr);
        assert(ev->eventExists(189, 200, 5060, -1) != nullptr);
        assert(ev->eventExists(200, 210, 10, -1) == nullptr);
        assert(ev->eventExists(170, 180, 100, -1) != nullptr);
        assert(ev->eventExists(0, 10, 10, -1) != nullptr);
        assert(ev->eventExists(0, 10, 100, -1) == nullptr);
        assert(ev->eventExists(70, 80, 100, -1) != nullptr);
        assert(ev->eventExists(10, 20, 20, -1) != nullptr);
        assert(ev->eventExists(150, 160, 30, -1) != nullptr);
        assert(ev->eventExists(150, 160, 40, -1) == nullptr);
        assert(ev->eventExists(0, 160, 190, -1) == nullptr);
        assert(ev->eventExists(0, 10, 1000, -1) == nullptr);
        assert(ev->eventExists(150, 200, 500, -1) != nullptr);

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


        auto ev1 = make_shared<RecurringItemEvent>("event", 0, 50, nullptr);

        assert(ev1->eventExists(50, 60, 60, -1) == nullptr);
        assert(ev1->eventExists(0, 10) != nullptr);
        assert(ev1->eventExists(50, 60) == nullptr);
        assert(ev1->eventExists(0, 10, 20, -1) != nullptr);

    }
    //RECURRING EVENT EXISTS TEST
    {
        auto rev = make_shared<RecurringEvent>("event", 150, 50, 100);
        assert(rev->eventExists(0, 10) == nullptr);
        assert(rev->eventExists(0, 50) == nullptr);
        assert(rev->eventExists(100, 150) == nullptr);
        assert(rev->eventExists(200, 210) == nullptr);
        assert(rev->eventExists(50, 100) == nullptr);
        assert(rev->eventExists(100, 151) != nullptr);
        assert(rev->eventExists(155, 160) != nullptr);
        assert(rev->eventExists(1055, 1100) != nullptr);
        assert(rev->eventExists(0, 5000) != nullptr);

        assert(rev->eventExists(100, 150, 100, -1) == nullptr);
        assert(rev->eventExists(200, 250, 100, -1) == nullptr);
        assert(rev->eventExists(100, 150, 200, -1) == nullptr);
        assert(rev->eventExists(150, 200, 100, -1) != nullptr);
        assert(rev->eventExists(25, 50, 50, -1) != nullptr);

        auto rev2 = make_shared<RecurringEvent>("event", 150, 50, 100, 500);
        assert(rev2->eventExists(500, 5000) == nullptr);
        assert(make_shared<RecurringEvent>("r1", 0, 10, 50, 300)->eventExists(0, 20));
        assert(make_shared<RecurringEvent>("r1", 0, 10, 50, 300)->eventExists(30, 60));
        assert(make_shared<RecurringEvent>("r1", 0, 10, 50, 300)->eventExists(100, 200));

    }
    //SINGLE EVENT EVENT MANAGER CHECK
    {

        EventManager e1;
        auto ev1 = make_shared<SingleEvent>("1", 10, 10);
        auto ev3 = make_shared<SingleEvent>("3", 100, 100);
        auto ev2 = make_shared<SingleEvent>("2", 30, 30);

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

        e1.addEvent(make_shared<RecurringEvent>("1", 10, 10, 100, 1010));
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

        auto rev1 = make_shared<RecurringEvent>("1", 0, 10, 50);
        auto rev2 = make_shared<RecurringEvent>("2", 20, 10, 50, 300);
        auto rev3 = make_shared<RecurringEvent>("3", 240, 10, 50, 1000);
        auto rev4 = make_shared<RecurringEvent>("4", 2110, 10, 50, 3000);

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

    }

    //EVENT MANAGER
    {
        EventManager e1;

        assert(e1.addEvent(make_shared<SingleEvent>("1", 0, 20)));
        assert(e1.addEvent(make_shared<SingleEvent>("2", 30, 60)));
        assert(e1.addEvent(make_shared<SingleEvent>("3", 100, 200)));
        assert(e1.addEvent(make_shared<RecurringEvent>("r1", 300, 10, 50, 600)));
        assert(!e1.addEvent(make_shared<RecurringEvent>("r1", 0, 10, 50, 300)));
        assert(drawEvents(e1.getEvents(30, 31)) == "2 30 90\n");
        assert(!e1.addEvent(make_shared<SingleEvent>("2", 30, 31)));
        assert(drawEvents(e1.getEvents(29, 30)).empty());
        assert(e1.addEvent(make_shared<SingleEvent>("2", 29, 1)));

        assert(drawEvents(e1.getEvents(1583859600, 1584223199)).empty());
    }
    //EVENT MANAGER DELETING SINGLE EVENTS
    {
        EventManager e1;
        auto ev1 = make_shared<SingleEvent>("1", 50, 10);
        auto ev5 = make_shared<SingleEvent>("5", 200, 30);
        auto ev2 = make_shared<SingleEvent>("2", 170, 10);
        auto ev3 = make_shared<SingleEvent>("3", 180, 1);
        auto ev4 = make_shared<SingleEvent>("4", 181, 10);
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
        e1.removeEvent(make_shared<SingleEvent>("test", 40, 5));
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
        assert(em.addEvent(make_shared<RecurringEvent>("event", 100, 50, 100)));
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
        em.removeEvent(evi4, Event::actionType::AllEvents);
        assert(drawEvents(em.getEvents(0, 500000)) == "");

        em.addEvent(make_shared<RecurringEvent>("title", 100, 50, 100, 1000));
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
        assert(em.addEvent(make_shared<SingleEvent>("title", 500, 500)));
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
        assert(em.addEvent(make_shared<RecurringEvent>("title", 500, 50, 100, 550)));
        assert(drawEvents(em.getEvents(0, 2000)) == "title 500 550\n");
        em.removeEvent(*em.getEvents(0, 2000).begin(), Event::AllEvents);
        assert(drawEvents(em.getEvents(0, 2000)).empty());
        assert(em.addEvent(make_shared<RecurringEvent>("title", 500, 50, 100, 550)));
        assert(drawEvents(em.getEvents(0, 2000)) == "title 500 550\n");
        em.removeEvent(*em.getEvents(0, 2000).begin(), Event::ThisAndNext);
        assert(drawEvents(em.getEvents(0, 2000)).empty());
        assert(em.addEvent(make_shared<RecurringEvent>("title", 500, 50, 100, 750)));
        em.removeEvent(*em.getEvents(600, 2000).begin(), Event::OnlyThis);
        assert(drawEvents(em.getEvents(0, 2000)) == "title 500 550\n"
                                                    "title 700 750\n");
        em.removeEvent(*em.getEvents(400, 2000).begin(), Event::AllEvents);
        assert(drawEvents(em.getEvents(0, 2000)).empty());

        assert(em.addEvent(make_shared<RecurringEvent>("title", 500, 50, 100, 750)));
        em.removeEvent(*em.getEvents(600, 2000).begin(), Event::OnlyThis);
        assert(drawEvents(em.getEvents(0, 2000)) == "title 500 550\n"
                                                    "title 700 750\n");
        em.removeEvent(*em.getEvents(400, 2000).begin(), Event::ThisAndNext);
        assert(drawEvents(em.getEvents(0, 2000)).empty());

        assert(em.addEvent(make_shared<RecurringEvent>("title", 500, 50, 100, 750)));
        em.removeEvent(*em.getEvents(600, 2000).begin(), Event::OnlyThis);
        assert(drawEvents(em.getEvents(0, 2000)) == "title 500 550\n"
                                                    "title 700 750\n");
        em.removeEvent(*em.getEvents(400, 2000).begin(), Event::OnlyThis);
        em.removeEvent(*em.getEvents(400, 2000).begin(), Event::OnlyThis);
        assert(drawEvents(em.getEvents(0, 2000)).empty());

        em.addEvent(make_shared<RecurringEvent>("title", 100, 50, 100, 1000));
        em.removeEvent(*em.getEvents(300, 350).begin(), Event::OnlyThis);
        assert(drawEvents(em.getEvents(0, 2000)) == "title 100 150\n"
                                                    "title 200 250\n"
                                                    "title 400 450\n"
                                                    "title 500 550\n"
                                                    "title 600 650\n"
                                                    "title 700 750\n"
                                                    "title 800 850\n"
                                                    "title 900 950\n");
        assert(em.addEvent(make_shared<SingleEvent>("single", 300, 50)));
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
        assert(em.addEvent(make_shared<RecurringEvent>("r", 300, 50, 1000)));
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
    //Moving events
    {
        EventManager em;
        em.addEvent(make_shared<SingleEvent>("single1", 500, 50));
        assert(drawEvents(em.getEvents(0, 1000)) == "single1 500 550\n");
        assert(em.moveEvent(*em.getEvents(0, 1000).begin(), 700));
        assert(drawEvents(em.getEvents(0, 1000)) == "single1 700 750\n");
        em.addEvent(make_shared<RecurringEvent>("recurring1", 1000, 100, 500));
        assert(em.moveEvent(*em.getEvents(1000, 1200).begin(), 1100));
        assert(em.moveEvent(*em.getEvents(1500, 1600).begin(), 1510));
        assert(drawEvents(em.getEvents(0, 2500)) == "single1 700 750\n"
                                                    "recurring1 1100 1200\n"
                                                    "recurring1 1510 1610\n"
                                                    "recurring1 2000 2100\n");
        assert(em.moveEvent(*em.getEvents(1500, 1610).begin(), 1500));
        assert(drawEvents(em.getEvents(0, 2500)) == "single1 700 750\n"
                                                    "recurring1 1100 1200\n"
                                                    "recurring1 1500 1600\n"
                                                    "recurring1 2000 2100\n");
        assert(em.moveEvent(*em.getEvents(2500, 2600).begin(), 2435));
        assert(drawEvents(em.getEvents(1500, 3500)) == "recurring1 1500 1600\n"
                                                       "recurring1 2000 2100\n"
                                                       "recurring1 2435 2535\n"
                                                       "recurring1 3000 3100\n");
        em.findByStart(2000)->setTitle("asdf");
        em.moveEvent(*em.findByTitle("asdf").begin(), 1750);
        assert(drawEvents(em.getEvents(1750, 3000)) == "asdf 1750 1850\n"
                                                       "asdf 2250 2350\n"
                                                       "recurring1 2435 2535\n"
                                                       "asdf 2750 2850\n");
        auto e = em.findByStart(2440);
        assert(em.changeDuration(e, 300));
        assert(drawEvents(em.getEvents(1750, 3000)) == "asdf 1750 1850\n"
                                                       "asdf 2250 2350\n"
                                                       "recurring1 2435 2735\n"
                                                       "asdf 2750 2850\n");

        assert(!em.changeDuration(em.findByStart(2440), 400));
        assert(drawEvents(em.getEvents(1750, 3000)) == "asdf 1750 1850\n"
                                                       "asdf 2250 2350\n"
                                                       "recurring1 2435 2735\n"
                                                       "asdf 2750 2850\n");
    }
    {
        EventManager em;
        assert(em.addEvent(make_shared<RecurringEvent>("r1", 0, 50, 100)));
        em.removeEvent(*em.getEvents(300, 400).begin());
        em.removeEvent(*em.getEvents(0, 400).begin(), Event::actionType::AllEvents);
        assert(drawEvents(em.getEvents(0, 1000)).empty());
        assert(em.addEvent(make_shared<SingleEvent>("e1", 200, 100)));
        assert(em.addEvent(make_shared<SingleEvent>("e2", 301, 100)));
        assert(em.addEvent(make_shared<SingleEvent>("e3", 300, 1)));
        assert(em.addEvent(make_shared<RecurringEvent>("r2", 500, 100, 200)));
        shared_ptr<Event> a = *em.getEvents(700, 800).begin();
        assert(em.moveEvent(a, 750));
        assert(drawEvents(em.getEvents(600, 1000)) == "r2 750 850\n"
                                                      "r2 900 1000\n");
        a = *em.getEvents(750, 850).begin();
        assert(!em.moveEvent(a, 801));
        assert(em.moveEvent(a, 800));
        assert(drawEvents(em.getEvents(600, 1000)) == "r2 800 900\n"
                                                      "r2 900 1000\n");
        assert(em.moveEvent(a, 600));
        assert(drawEvents(em.getEvents(600, 1000)) == "r2 600 700\n"
                                                      "r2 900 1000\n");
    }
    // Editing events
    {
        auto event = make_shared<SingleEvent>("TitleOG", 100, 100);
        event->addPerson(make_shared<Person>("karel", "pepa"));
        assert(event->getTitle() == "TitleOG");
        event->setTitle("Title2");
        assert(event->getTitle() == "Title2");
        event->setLocation("location");
        assert(event->getLocation() == "location");
        event->setEditable(false);
        try {
            event->setTitle("titi");
            assert(false);
        }
        catch (EventNotEditableException &e) {}
        try {
            event->setEditable(true);
            assert(false);
        }
        catch (EventNotEditableException &e) {}
        try {
            event->setLocation("titi");
            assert(false);
        }
        catch (EventNotEditableException &e) {}

        try {
            event->setStartDateUtc(50);
            assert(false);
        }
        catch (EventNotEditableException &e) {}
        try {
            event->setDurationUtc(50);
            assert(false);
        }
        catch (EventNotEditableException &e) {}
        try {
            event->addPerson(make_shared<Person>("name", "surname"));
            assert(false);
        }
        catch (EventNotEditableException &e) {}
        try {
            auto a = event->getPeople()[0];
            event->removePerson(a);
            assert(false);
        }
        catch (EventNotEditableException &e) {}
    }
    {
        auto rec = make_shared<RecurringEvent>("T1", 0, 100, 1000);
        EventManager ev;
        ev.addEvent(rec);
        ev.removeEvent(*ev.getEvents(3000, 4000).begin());
        auto event = *ev.getEvents(4000, 5000).begin();
        event->setTitle("T2");
        ev.removeEvent(*ev.getEvents(0, 1000).begin());
        event = *ev.getEvents(1000, 2000).begin();
        assert(event->getTitle() == "T2");
    }
    //COPY CONSTRUCTOR
    {
        auto rec1 = make_shared<RecurringEvent>("Title", 0, 50, 500);
        auto event1 = (*rec1->getEvents(1000, 1100).begin())->freeSelf(Event::actionType::OnlyThis);
        shared_ptr<RecurringEvent> ev = make_shared<RecurringEvent>(*rec1);
        auto event2 = (*rec1->getEvents(5500, 6000).begin())->freeSelf(Event::actionType::ThisAndNext);
        assert(drawEvents(ev->getEvents(5000, 10000)) == "Title 5000 5050\n"
                                                         "Title 5500 5550\n"
                                                         "Title 6000 6050\n"
                                                         "Title 6500 6550\n"
                                                         "Title 7000 7050\n"
                                                         "Title 7500 7550\n"
                                                         "Title 8000 8050\n"
                                                         "Title 8500 8550\n"
                                                         "Title 9000 9050\n"
                                                         "Title 9500 9550\n");
        assert(drawEvents(rec1->getEvents(5000, 10000)) == "Title 5000 5050\n");

        EventManager e;
        e.addEvent(ev);
        e.removeEvent(*e.getEvents(1500, 2000).begin(), Event::actionType::OnlyThis);
        (*e.findByTitle("Title").begin())->setEditable(false);
        e.removeEvent(*e.getEvents(2500, 3000).begin(), Event::actionType::OnlyThis);
        assert(drawEvents(e.getEvents(2000, 2500)) == "Title 2000 2050\n");
        e.removeEvent(*e.getEvents(2000, 2500).begin(), Event::actionType::OnlyThis);
        assert(drawEvents(e.getEvents(2000, 2500)).empty());
        assert(drawEvents(e.getEvents(0, 2500)) == "Title 0 50\n"
                                                   "Title 500 550\n");

        auto ev0 = make_shared<SingleEvent>("single", 0, 50);
        ev0->setTitle("test");
        auto ev1 = make_shared<SingleEvent>(*ev0);
        ev0->setEditable(false);
        assert(ev1->getTitle() == "test");
        ev1->setTitle("tit");
        assert(ev0->getTitle() == "test");
    }
    //Export import
    {
        auto event = make_shared<SingleEvent>(R"(\\\\dlakjf\;\\\;\;\\\\\;)", 0, 100);
        event->addPerson(make_shared<Person>("name", "surname"));
        event->setLocation("praha");
        string e = event->exportEvent();
        auto import = FileUtility::fromString(e);
        assert(import->infoAll() == event->infoAll());
        auto recurring = make_shared<RecurringEvent>(R"(\;\\\\\\\\\\est\;adlsfja\\)", 500, 100, 1000, 3000);
        e = recurring->exportEvent();
        import = import = FileUtility::fromString(e);
        (*recurring->getEvents(1500, 2000).begin())->freeSelf(Event::actionType::OnlyThis);
        e = recurring->exportEvent();
        import = import = FileUtility::fromString(e);
        assert(import->infoAll() == recurring->infoAll());


    }
    {
        EventManager ev;
        ev.addEvent(make_shared<SingleEvent>("c", 140400, 7980));
        ev.addEvent(make_shared<SingleEvent>("this event has a very very very long name", 87000, 960));
        ev.addEvent(make_shared<SingleEvent>("c", 88380, 1000));
        ev.addEvent(make_shared<SingleEvent>("this event starts before the day", 82380, 960));
        ev.addEvent(make_shared<SingleEvent>("this event ends after the day", 168360, 960 * 2));
        auto a = make_shared<SingleEvent>("a", 1590562800, 3600 * 6);
        a->addPerson(make_shared<Person>("Karel", "Slepicka"));
        a->addPerson(make_shared<Person>("Ahoj", "Pepo"));
        a->addPerson(make_shared<Person>("areg", "adsflj"));
        ev.addEvent(a);
        ev.addEvent(make_shared<SingleEvent>("b", 1590361200, 3600 * 6));
        ev.addEvent(make_shared<SingleEvent>("c", 1590706800, 100000));
        ev.addEvent(make_shared<SingleEvent>("d", 1590447600, 3600 * 6));
        ev.addEvent(make_shared<SingleEvent>("f", 108000, 3600 * 6));
        ev.addEvent(make_shared<SingleEvent>("f", 1590505200, 3600 * 8));

        istringstream in("create single t1 28-05-2020T12:01 119-minute\ncreate single t2 28-05-2020T14:00 4-hour\ndraw day");
        ostringstream out;
        Interface i(in, out, ev);
        i.start();
    }
    {
        istringstream in("create single single1 02-06-2020T12:02 1-hour\n"
                         "create single single2 02-06-2020T12:02 1-hour\ny\n"
                         "create recurring\nrecurring1\n01-06-2020T12:00\n1-hour\n1-day\n\ny\ndraw day\ndraw set 02-06-2020\n");
        ostringstream out;
        EventManager e;
        Interface i(in, out, e);
        i.start();

    }
    {
        CalendarApp app;
        app.start();
    }
    cout << "end" << endl;

    return 0;
}

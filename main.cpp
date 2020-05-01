#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <assert.h>
#include <set>
#include "Calendar/EventManager.h"
#include "Utility/EventSet.h"

using namespace std;

string drawEvents(const EventSet<Event> &s) {
    stringstream ss;
    for (auto event : s) {
        ss << event->getTitle() << " " << event->getStartDateUtc() << " " << event->getEndDateUtc() << endl;
    }
    return ss.str();
}

int main() {
    //EVENTSET BASIC TEST
    {
        EventSet<Event> *s = new EventSet<Event>;
        Event *ev5 = new SingleEvent("t5", 160, 10);
        Event *ev2 = new SingleEvent("t2", 50, 10);
        Event *ev3 = new SingleEvent("t3", 70, 10);
        Event *ev1 = new SingleEvent("t1", 10, 20);
        Event *ev4 = new SingleEvent("t4", 120, 30);

        s->refInsert(ev2);
        s->refInsert(ev1);
        s->refInsert(ev3);
        s->refInsert(ev4);
        s->refInsert(ev5);

        ev2->removeReference();
        ev1->removeReference();
        ev3->removeReference();
        ev4->removeReference();
        ev5->removeReference();
        assert(drawEvents(*s) == "t1 10 30\n"
                                 "t2 50 60\n"
                                 "t3 70 80\n"
                                 "t4 120 150\n"
                                 "t5 160 170\n");

        delete s;
    }
    //EVENTSET COPY, ASSIGMENT
    {
        EventSet<Event> s;

        Event *ev5 = new SingleEvent("t5", 160, 10);
        Event *ev2 = new SingleEvent("t2", 50, 10);
        Event *ev3 = new SingleEvent("t3", 70, 10);
        Event *ev1 = new SingleEvent("t1", 10, 20);
        Event *ev4 = new SingleEvent("t4", 120, 30);

        s.refInsert(ev2);
        s.refInsert(ev1);
        s.refInsert(ev3);
        s.refInsert(ev4);
        s.refInsert(ev5);

        ev2->removeReference();
        ev1->removeReference();
        ev3->removeReference();
        ev4->removeReference();
        ev5->removeReference();

        EventSet<Event> s2 = s;
        assert(drawEvents(s) == "t1 10 30\n"
                                "t2 50 60\n"
                                "t3 70 80\n"
                                "t4 120 150\n"
                                "t5 160 170\n");
        assert(drawEvents(s2) == "t1 10 30\n"
                                 "t2 50 60\n"
                                 "t3 70 80\n"
                                 "t4 120 150\n"
                                 "t5 160 170\n");
        s.refErase(s.begin());

        assert(drawEvents(s) == "t2 50 60\n"
                                "t3 70 80\n"
                                "t4 120 150\n"
                                "t5 160 170\n");
        assert(drawEvents(s2) == "t1 10 30\n"
                                 "t2 50 60\n"
                                 "t3 70 80\n"
                                 "t4 120 150\n"
                                 "t5 160 170\n");
        auto r1 = new RecurringEvent("r1", 200, 10, 100, 600);
        s2.refInsert(r1);
        r1->removeReference();
        assert(drawEvents(s) == "t2 50 60\n"
                                "t3 70 80\n"
                                "t4 120 150\n"
                                "t5 160 170\n");
        assert(drawEvents(s2) == "t1 10 30\n"
                                 "t2 50 60\n"
                                 "t3 70 80\n"
                                 "t4 120 150\n"
                                 "t5 160 170\n"
                                 "r1 200 210\n");
        auto tmp = s.begin();
        tmp++;
        tmp++;
        s.refErase(tmp);
        assert(drawEvents(s) == "t2 50 60\n"
                                "t3 70 80\n"
                                "t5 160 170\n");
        s2.refErase(s2.begin(), --s2.end());
        assert(drawEvents(s2) == "r1 200 210\n");

        s2 = s;

        assert(drawEvents(s) == "t2 50 60\n"
                                "t3 70 80\n"
                                "t5 160 170\n");
        assert(drawEvents(s2) == "t2 50 60\n"
                                 "t3 70 80\n"
                                 "t5 160 170\n");


    }
    //SINGLE EVENT EVENT MANAGER CHECK
    {

        EventManager e1;
        auto ev1 = new SingleEvent("1", 10, 10);
        auto ev3 = new SingleEvent("3", 100, 100);
        auto ev2 = new SingleEvent("2", 30, 30);

        e1.addEvent(ev3);
        e1.addEvent(ev1);
        e1.addEvent(ev2);

        ev1->removeReference();
        ev2->removeReference();
        ev3->removeReference();

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
        auto rev1 = new RecurringEvent("1", 10, 10, 100, 1010);
        e1.addEvent(rev1);
        rev1->removeReference();
        assert(drawEvents(e1.getEvents(550, 800)) == "1 610 620\n"
                                                     "1 710 720\n");
        assert(drawEvents(e1.getEvents(1000, 3000)).empty());
        assert(drawEvents(e1.getEvents(0, 15)) == "1 10 20\n");
        assert(drawEvents(e1.getEvents(14, 15)) == "1 10 20\n");
        assert(drawEvents(e1.getEvents(14, 110)) == "1 10 20\n");
        assert(drawEvents(e1.getEvents(0, 30)) == "1 10 20\n");
    }
    //RECURRING EVENTS 2
    {
        EventManager e1;
        EventManager e2;

        auto rev1 = new RecurringEvent("1", 0, 10, 50);
        auto rev2 = new RecurringEvent("2", 20, 10, 50, 300);
        auto rev3 = new RecurringEvent("3", 240, 10, 50, 1000);
        auto rev4 = new RecurringEvent("4", 2110, 10, 50, 3000);

        e1.addEvent(rev1);
        e1.addEvent(rev4);
        e1.addEvent(rev3);
        e1.addEvent(rev2);

        e2.addEvent(rev4);

        rev1->removeReference();
        rev2->removeReference();
        rev3->removeReference();
        rev4->removeReference();

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
    /*
    {
        EventManager e1;

        e1.addEvent(new SingleEvent("1", 0, 20));
        e1.addEvent(new SingleEvent("2", 30, 60));
        e1.addEvent(new SingleEvent("3", 100, 200));
        e1.addEvent(new RecurringEvent("r1", 0, 10, 50, 300));

        cout << drawEvents(e1.getEvents(1583859600, 1584223199));
        assert(drawEvents(e1.getEvents(1583859600, 1584223199)) == "");
    }
     */
    cout << "end" << endl;
    return 0;
}

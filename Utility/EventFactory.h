/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 02.06.2020
 */

#ifndef CALENDAR_EVENTFACTORY_H
#define CALENDAR_EVENTFACTORY_H

#include "../Calendar/Event.h"
#include "../Calendar/SingleEvent.h"
#include "../Calendar/RecurringEvent.h"
#include "Exceptions/InvalidEventSequenceException.h"

struct EventFactory {
    static shared_ptr<Event> fromString(const string &event) {
        istringstream ss(event);
        string type = readNext(ss, ';');
        if (type == "singleevent")
            return make_shared<SingleEvent>(SingleEvent(ss));
        else if (type == "recurringevent")
            return make_shared<RecurringEvent>(RecurringEvent(ss));
        else
            throw InvalidEventSequenceException();
    };

    static string readNext(istringstream &input, char separator) {
        stringstream res;
        while (true) {
            char c = input.get();
            if (c == '\\') {
                c = input.get();
            }
            if (c == separator)
                break;
            res << c;
        }
        string result = res.str();
        return result;
    };
};

#endif //CALENDAR_EVENTFACTORY_H

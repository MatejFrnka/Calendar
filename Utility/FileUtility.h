/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 02.06.2020
 */

#ifndef CALENDAR_FILEUTILITY_H
#define CALENDAR_FILEUTILITY_H

#include <fstream>
#include "../Calendar/Event.h"
#include "../Calendar/SingleEvent.h"
#include "../Calendar/RecurringEvent.h"
#include "Exceptions/InvalidEventSequenceException.h"

struct FileUtility {
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
            if (c == separator)
                break;
            if (c == '\\') {
                c = input.get();
            }
            res << c;
        }
        string result = res.str();
        return result;
    };

    static bool saveData(const string &data) {
        ofstream file;
        file.open("events_saved.evs", ios::out | ios::trunc);
        file << data;
        return !file.fail();
    }

    static vector<string> readData() {
        ifstream file;
        file.open("events_saved.evs", ios::in);
        string line;
        vector<string> result;
        while (getline(file, line, '\n')) {
            result.push_back(line);
        }
        return result;
    }
};

#endif //CALENDAR_FILEUTILITY_H

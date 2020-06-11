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
#include "../Calendar/EventManager.h"
#include <ostream>

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

    static bool saveData(const string &data, const string &path = "events_saved.evs") {
        ofstream file;
        file.open(path, ios::out | ios::trunc);
        if (!file.is_open())
            return false;
        file << data;
        return !file.fail();
    }

    /**
     * Loads events from file
     * @param eventManager event manager to load events into
     * @throws invalid_argument when supplied path does not work
     * @return false if loading of at least one event failed
     */

    static vector<string> readData(const string &path = "events_saved.evs") {
        ifstream file;
        file.open(path, ios::in);
        if (!file.is_open())
            throw invalid_argument("Invalid file path\n");
        string line;
        vector<string> result;
        while (getline(file, line, '\n')) {
            result.push_back(line);
        }
        return result;
    }

    static bool load(EventManager &eventManager, ostream &out, const string &path = "events_saved.evs") {
        vector<string> data;
        try {
            data = FileUtility::readData(path);
        }
        catch (invalid_argument &e) {
            out << e.what();
            return false;
        }
        size_t failedLoads = 0;
        for (const auto &f:data) {
            try {
                if (!eventManager.addEvent(f))
                    failedLoads++;
            }
            catch (InvalidEventSequenceException &e) {
                failedLoads++;
            }
        }
        if (failedLoads > 0) {
            out << "Failed to load " << failedLoads << " events" << endl;
        }
        return true;
    }
};

#endif //CALENDAR_FILEUTILITY_H

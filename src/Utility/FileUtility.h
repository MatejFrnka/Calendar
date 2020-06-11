/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 02.06.2020
 */

#pragma once
#include <fstream>
#include "../Calendar/Event.h"
#include "../Calendar/SingleEvent.h"
#include "../Calendar/RecurringEvent.h"
#include "Exceptions/InvalidEventSequenceException.h"
#include "../Calendar/EventManager.h"
#include <ostream>

struct FileUtility {
    static std::shared_ptr<Event> fromString(const std::string &event) {
        std::istringstream ss(event);
        std::string type = readNext(ss, ';');
        if (type == "singleevent")
            return std::make_shared<SingleEvent>(SingleEvent(ss));
        else if (type == "recurringevent")
            return std::make_shared<RecurringEvent>(RecurringEvent(ss));
        else
            throw InvalidEventSequenceException();
    };

    static std::string readNext(std::istringstream &input, char separator) {
        std::stringstream res;
        while (true) {
            char c = input.get();
            if (c == separator)
                break;
            if (c == '\\') {
                c = input.get();
            }
            res << c;
        }
        std::string result = res.str();
        return result;
    };

    static bool saveData(const std::string &data, const std::string &path = "events_saved.evs") {
        std::ofstream file;
        file.open(path, std::ios::out | std::ios::trunc);
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

    static std::vector<std::string> readData(const std::string &path = "events_saved.evs") {
        std::ifstream file;
        file.open(path, std::ios::in);
        if (!file.is_open())
            throw std::invalid_argument("Invalid file path\n");
        std::string line;
        std::vector<std::string> result;
        while (getline(file, line, '\n')) {
            result.push_back(line);
        }
        return result;
    }

    static bool load(EventManager &eventManager, std::ostream &out, const std::string &path = "events_saved.evs") {
        std::vector<std::string> data;
        try {
            data = FileUtility::readData(path);
        }
        catch (std::invalid_argument &e) {
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
            out << "Failed to load " << failedLoads << " events" << std::endl;
        }
        return true;
    }
};


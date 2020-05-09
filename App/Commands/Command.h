/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 06.05.2020
 */

#ifndef CALENDAR_APP_ACTION
#define CALENDAR_APP_ACTION

#include <string>
#include <utility>
#include <ostream>
#include <vector>

struct Command {

    Command() = delete;

    Command(std::string name_, std::string description_, std::ostream &out_) : name(std::move(name_)), description(std::move(description_)), out(out_) {}

    enum outcome {
        Success,
        Failed,
    };

    virtual outcome executeAction(std::vector<std::string> parameters) = 0;

    const std::string name;
    const std::string description;
    std::ostream &out;

    friend std::ostream &operator<<(std::ostream &ostream, const Command &cmd) {
        return ostream << cmd.name << ":\t" << cmd.description << std::endl;
    }
};

#endif

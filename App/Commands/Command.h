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
#include <memory>

class Command {
public:
    Command() = delete;

    Command(std::string name_, std::string description_, std::ostream &out_) : name(std::move(name_)), description(std::move(description_)), out(out_) {}

    virtual std::vector<std::shared_ptr<Command>> executeAction(const std::vector<std::string> &parameters) = 0;

    const std::vector<std::shared_ptr<Command>> &getSubCommands() const { return commands; }

    const std::string name;
    const std::string description;
    std::ostream &out;

    friend std::ostream &operator<<(std::ostream &ostream, const Command &cmd) {
        return ostream << cmd.name << ":\t" << cmd.description;
    }

protected:
    std::vector<std::shared_ptr<Command>> commands;
};

#endif

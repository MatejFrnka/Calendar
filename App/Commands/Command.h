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

    Command(std::string name_, std::string description_, std::ostream &out_) : name(std::move(name_)), description(std::move(description_)), out(out_) {}

    /**
     * Executes command's action
     * @param parameters parameters to action
     * @return Options for commands after this commands execution
     */
    virtual std::vector<std::shared_ptr<Command>> executeAction(const std::vector<std::string> &parameters) = 0;

    /**
     * @return commands that can be executed after executing this command
     */
    const std::vector<std::shared_ptr<Command>> &getSubCommands() const { return commands; }

    const std::string name;
    const std::string description;


    friend std::ostream &operator<<(std::ostream &ostream, const Command &cmd) {
        return ostream << cmd.name << ":\t" << cmd.description;
    }

    std::ostream &out;
protected:
    std::vector<std::shared_ptr<Command>> commands;
};

#endif

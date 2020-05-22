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
#include "../../Utility/InputUtility.h"

class Command {
public:

    Command(std::string name_, std::string description_, InputUtility &inputUtility_) : name(std::move(name_)), description(std::move(description_)), inputUtility(inputUtility_) {}



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

    InputUtility &inputUtility;
protected:
    std::vector<std::shared_ptr<Command>> commands;
};

#endif

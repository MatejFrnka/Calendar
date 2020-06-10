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
#include <map>

class Command {
public:

    Command(std::string name_,
            std::string description_,
            InputUtility &inputUtility_,
            std::map<std::string, std::string> parameters_ = std::map<std::string, std::string>()) : name(std::move(name_)),
                                                                                                     description(std::move(description_)),
                                                                                                     inputUtility(inputUtility_),
                                                                                                     params(std::move(parameters_)) {}

    virtual ~Command() = default;

    /**
     * Executes command's action
     * @param parameters parameters to action
     * @return Options for commands after this commands execution
     */
    virtual std::vector<std::shared_ptr<Command>> executeAction(std::queue<std::string> &parameters) = 0;

    /**
     * @return commands that can be executed after executing this command
     */
    const std::vector<std::shared_ptr<Command>> &getSubCommands() const { return commands; }

    /**
     * Command name - command is executed when user enters its name
     */
    const std::string name;
    /**
     * Command description - is displayed by help command, it should describe what the command does
     */
    const std::string description;


    friend std::ostream &operator<<(std::ostream &ostream, const Command &cmd) {
        return ostream << cmd.name << ":\t" << cmd.description;
    }

    InputUtility &inputUtility;
    /**
     * Parameters that the function takes
     */
    const std::map<std::string, std::string> params;
protected:
    /**
     * Commands that the function will return
     */
    std::vector<std::shared_ptr<Command>> commands;
};

#endif

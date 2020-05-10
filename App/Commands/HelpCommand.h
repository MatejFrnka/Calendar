/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 09.05.2020
 */

#ifndef CALENDAR_APP_COMMANDS_HELP_COMMAND
#define CALENDAR_APP_COMMANDS_HELP_COMMAND

#include "Command.h"
#include <utility>
#include <vector>
#include <memory>

class HelpCommand : public Command {
public:
    HelpCommand(const std::vector<std::shared_ptr<Command>> &commands_, std::ostream &out_) : Command("help", "", out_), refCommands(commands_) {

    }

    std::vector<std::shared_ptr<Command>> executeAction(const std::vector<std::string> &parameters) override {
        printCommandsRec(refCommands, 0);
        return refCommands;
    };

private:
    void printCommandsRec(const std::vector<std::shared_ptr<Command>> &toPrint, int depth) const {
        depth++;
        for (const auto &it : toPrint) {
            for (int i = 1; i < depth; ++i) {
                if (i == 1) {
                    out << "|- ";
                } else
                    out << "-- ";
            }
            out << *it << std::endl;
            printCommandsRec(it->getSubCommands(), depth);
        }
    }

    const std::vector<std::shared_ptr<Command>> &refCommands;
};

#endif


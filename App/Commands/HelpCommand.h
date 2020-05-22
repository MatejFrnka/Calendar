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
    HelpCommand(const std::vector<std::shared_ptr<Command>> &commands_, InputUtility &inputUtility_) : Command("help", "", inputUtility_), refCommands(commands_) {

    }

    std::vector<std::shared_ptr<Command>> executeAction(const std::vector<std::string> &parameters) override;

private:
    void printCommandsRec(const std::vector<std::shared_ptr<Command>> &toPrint, int depth) const;

    const std::vector<std::shared_ptr<Command>> &refCommands;
};

#endif


/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 06.05.2020
 */

#include "Interface.h"

void Interface::start() {
    std::string input;
    std::vector<std::shared_ptr<Command>> currentActions;
    while (std::getline(in, input)) {
        if (currentActions.empty())
            currentActions = executeAction(input, homeCommands);
        else
            currentActions = executeAction(input, currentActions);
    }
}

Interface::Interface(std::istream &in_, std::ostream &out_) : in(in_), out(out_) {
    homeCommands.push_back(std::make_shared<CreateCommand>(out, eventManager));
    homeCommands.push_back(std::make_shared<DeleteCommand>(out));
}

std::vector<std::shared_ptr<Command>> Interface::executeAction(const std::string &commandName, const std::vector<std::shared_ptr<Command>> &commands) {

    std::vector<std::string> params = InputUtility::getParams(commandName);
    if (params.empty())
        return std::vector<std::shared_ptr<Command>>();

    if (commandName == "help") {
        HelpCommand cmd(commands, out);
        return cmd.executeAction(params);
    }

    for (const auto &item : commands) {
        if (item->name == params[0])
            return item->executeAction(std::vector<std::string>(params.begin() + 1, params.end()));
    }
    out << params[0] << " not found. Type help for all commands" << std::endl;
    return std::vector<std::shared_ptr<Command>>();

}

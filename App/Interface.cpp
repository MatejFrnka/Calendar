/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 06.05.2020
 */

#include "Interface.h"
#include "Commands/DrawCommand.h"
#include "Commands/SelectCommand.h"

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

Interface::Interface(std::istream &in_, std::ostream &out_, EventManager &eventManager_) : in(in_), out(out_), inputUtility(in_, out_), eventManager(eventManager_),
                                                                                           drawManager(eventManager_, out_) {
    homeCommands.push_back(std::make_shared<CreateCommand>(inputUtility, eventManager));
    homeCommands.push_back(std::make_shared<DrawCommand>(inputUtility, drawManager));
    homeCommands.push_back(std::make_shared<SelectCommand>(inputUtility, eventManager));
}

std::vector<std::shared_ptr<Command>> Interface::executeAction(const std::string &commandName, const std::vector<std::shared_ptr<Command>> &commands) {

    std::queue<std::string> params = InputUtility::getParams(commandName);

    if (commandName.empty())
        return commands;
    if (commandName == "cancel")
        return std::vector<std::shared_ptr<Command>>();


    if (commandName == "help") {
        HelpCommand cmd(commands, inputUtility);
        return cmd.executeAction(params);
    }

    for (const auto &item : commands) {
        if (item->name == params.front()) {
            params.pop();
            auto res = item->executeAction(params);
            if (!params.empty()) {
                inputUtility.out << "'";
                while (!params.empty()) {
                    inputUtility.out << params.front() << ' ';
                    params.pop();
                }
                inputUtility.out << "' in '" << commandName << "' was discarded and had no effect" << std::endl;
            }
            return res;
        }
    }
    out << commandName << " not found. Type help for all commands" << std::endl;
    return commands;

}
/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 06.05.2020
 */

#include "Interface.h"
#include "Commands/DrawCommand.h"
#include "Commands/SelectCommand.h"
#include "../Utility/Exceptions/UnexpectedEndOfInputException.h"
#include "Commands/ExportCommand.h"
#include "Commands/ImportCommand.h"

void Interface::start() {
    std::string input;
    std::vector<std::shared_ptr<Command>> currentActions;
    while (std::getline(in, input)) {
        try {
            if (input == "exit")
                break;
            if (currentActions.empty())
                currentActions = executeAction(input, homeCommands);
            else
                currentActions = executeAction(input, currentActions);
        }
        catch (UnexpectedEndOfInputException &e) {
            out << "Command was canceled" << std::endl;
        }
        catch (std::invalid_argument &e) {
            out << e.what() << std::endl;
        }
    }
}

Interface::Interface(std::istream &in_, std::ostream &out_, EventManager &eventManager_) : in(in_), out(out_), inputUtility(in_, out_), eventManager(eventManager_),
                                                                                           drawManager(eventManager_, out_) {
    homeCommands.push_back(std::make_shared<CreateCommand>(inputUtility, eventManager));
    homeCommands.push_back(std::make_shared<DrawCommand>(inputUtility, drawManager));
    homeCommands.push_back(std::make_shared<SelectCommand>(inputUtility, eventManager));
    homeCommands.push_back(std::make_shared<ExportCommand>(inputUtility, eventManager));
    homeCommands.push_back(std::make_shared<ImportCommand>(inputUtility, eventManager));

}

std::vector<std::shared_ptr<Command>> Interface::executeAction(std::queue<std::string> &params, const std::vector<std::shared_ptr<Command>> &commands) {
    if (params.empty())
        return commands;
    if (params.front() == "cancel")
        return std::vector<std::shared_ptr<Command>>();

    if (params.front() == "help") {
        HelpCommand cmd(commands, inputUtility);
        return cmd.executeAction(params);
    }

    for (const auto &item : commands) {
        if (item->name == params.front()) {
            params.pop();
            auto res = item->executeAction(params);
            return executeAction(params, res);
        }
    }
    out << params.front() << " not found. Type help for all commands" << std::endl;
    return commands;
}

std::vector<std::shared_ptr<Command>> Interface::executeAction(const std::string &commandName, const std::vector<std::shared_ptr<Command>> &commands) {
    std::queue<std::string> params = InputUtility::getParams(commandName);
    return executeAction(params, commands);
}
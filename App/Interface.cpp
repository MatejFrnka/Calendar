/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 06.05.2020
 */

#include "Interface.h"

void Interface::start() {
    std::string input;
    while (std::getline(in, input)) {
        executeAction(input, homeCommands);
    }
}

Interface::Interface(std::istream &in_, std::ostream &out_) : in(in_), out(out_) {
    std::cout << "test";
    homeCommands.push_back(std::make_unique<CreateCommand>(out));
}

Command::outcome Interface::executeAction(const std::string &commandName, const std::vector<std::unique_ptr<Command>> &commands) {
    //TODO: read params from commandName
    std::vector<std::string> params;
    if (commandName == "help") {
        HelpCommand cmd(commands, out);
        return cmd.executeAction(params);
    }

    for (const auto &item : commands) {
        if (item->name == commandName)
            return item->executeAction(params);
    }
    out << commandName << " not found. Type help for all commands" << std::endl;
    return Command::outcome::Failed;
}

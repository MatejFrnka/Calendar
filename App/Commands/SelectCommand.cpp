/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 26.05.2020
 */

#include "SelectCommand.h"
#include "CustomCommand.h"

SelectCommand::SelectCommand(InputUtility &inputUtility, EventManager &eventManager)
        : Command("select", "Selects an event", inputUtility, std::map<std::string, std::string>{{"date",  "Selects event by date"},
                                                                                                 {"title", "Selects event by title"},
                                                                                                 {"place", "Selects date by location"}}) {}

std::vector<std::shared_ptr<Command>> SelectCommand::executeAction(const std::vector<std::string> &parameters) {
    if (parameters.empty()) {
        inputUtility.noParameterFound();
        return std::vector<std::shared_ptr<Command>>();
    } else if (parameters[0] == "date") {
        inputUtility.out << "not implemented yet";
    } else if (parameters[0] == "title") {
        inputUtility.out << "not implemented yet";
    } else if (parameters[0] == "place") {
        inputUtility.out << "not implemented yet";
    } else
        inputUtility.noParameterFound(parameters[0]);
    return commands;
}



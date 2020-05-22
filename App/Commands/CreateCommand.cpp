/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 10.05.2020
 */

#include "CreateCommand.h"

CreateCommand::CreateCommand(InputUtility &inputUtility, EventManager &eventManager) : Command("create", "Used to create a new event", inputUtility) {
    //TODO:ADD PROPER DESCRIPTION
    CustomCommand single("single",
                         "Single event happens only once.",
                         inputUtility,
                         [&eventManager](const std::vector<std::string> &params, CustomCommand &self) {
                             //Gathering event info
                             auto title = self.inputUtility.readString("Title", params.empty() ? "" : params[0]);
                             auto startUtc = self.inputUtility.readDate("Start", params.size() <= 1 ? "" : params[1]);
                             auto Duration = self.inputUtility.readTimeSpan("Duration", params.size() <= 2 ? "" : params[2]);

                             eventManager.addEvent(SingleEvent::getInstance(title, startUtc, Duration));
                             self.inputUtility.out << "creating single event... -  ui not implemented yet\n";
                             return std::vector<std::shared_ptr<Command>>();
                         });
    commands.push_back(make_shared<CustomCommand>(single));

    CustomCommand recurring("recurring",
                            "todo todo",
                            inputUtility,
                            [](const std::vector<std::string> &params, CustomCommand &self) {
                                std::vector<std::shared_ptr<Command>> result;
                                self.inputUtility.out << "creating recurring event... -  ui not implemented yet";
                                return result;
                            });
    commands.push_back(make_shared<CustomCommand>(recurring));
}

std::vector<std::shared_ptr<Command>> CreateCommand::executeAction(const std::vector<std::string> &parameters) {
    if (!parameters.empty())
        for (const auto &command : getSubCommands()) {
            if (command->name == parameters[0])
                return command->executeAction(std::vector<std::string>(parameters.begin() + 1, parameters.end()));
        }
    return commands;
}

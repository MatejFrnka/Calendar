/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 10.05.2020
 */

#include "CreateCommand.h"

CreateCommand::CreateCommand(InputUtility &inputUtility, EventManager &eventManager) : Command("create", "Used to create a new event", inputUtility) {
    CustomCommand single("single",
                         "Single event that happens only once.",
                         inputUtility,
                         [&eventManager](std::queue<std::string> &params, CustomCommand &self) {
                             //Gathering event info
                             auto title = self.inputUtility.readString("Title", params);
                             auto startUtc = self.inputUtility.readDateTime("Start", params);
                             auto Duration = self.inputUtility.readTimeSpan("Duration", params);

                             eventManager.addEvent(SingleEvent::getInstance(title, startUtc, Duration));
                             self.inputUtility.out << "creating single event... -  ui not implemented yet\n";
                             return std::vector<std::shared_ptr<Command>>();
                         });
    commands.push_back(make_shared<CustomCommand>(single));

    CustomCommand recurring("recurring",
                            "todo todo",
                            inputUtility,
                            [](std::queue<std::string> &params, CustomCommand &self) {
                                std::vector<std::shared_ptr<Command>> result;
                                self.inputUtility.out << "creating recurring event... -  ui not implemented yet";
                                return result;
                            });
    commands.push_back(make_shared<CustomCommand>(recurring));
}

std::vector<std::shared_ptr<Command>> CreateCommand::executeAction(std::queue<std::string> &parameters) {
    if (!parameters.empty())
        for (const auto &command : getSubCommands()) {
            if (command->name == parameters.front()) {
                parameters.pop();
                return command->executeAction(parameters);
            }
        }
    return commands;
}

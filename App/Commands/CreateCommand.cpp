/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 10.05.2020
 */

#include <cstring>
#include "CreateCommand.h"

CreateCommand::CreateCommand(InputUtility &inputUtility, EventManager &eventManager) : Command("create", "Used to create a new event", inputUtility) {
    CustomCommand single("single",
                         "Single event that happens only once.",
                         inputUtility,
                         [&eventManager](std::queue<std::string> &params, CustomCommand &self) {
                             //Gathering event info
                             auto title = self.inputUtility.readString("Title", params);
                             auto startUtc = self.inputUtility.readDateTime("Start", params);
                             auto duration = self.inputUtility.readTimeSpan("Duration", params);

                             if (!eventManager.addEvent(SingleEvent::getInstance(title, startUtc, duration))) {
                                 time_t firstFree = eventManager.findFreeSpace(startUtc, duration);
                                 tm tm_firstFree = *localtime(&firstFree);
                                 self.inputUtility.out << "Another event is happening during given time. Do you want to move event to next available time - "
                                                       << asctime(&tm_firstFree);
                                 if (self.inputUtility.readBool("Move event"))
                                     eventManager.addEvent(SingleEvent::getInstance(title, firstFree, duration));
                                 else {
                                     return std::vector<std::shared_ptr<Command>>();
                                 }
                             }
                             self.inputUtility.out << "Event was created" << endl;
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

/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 26.05.2020
 */

#ifndef CALENDAR_INFOCOMMAND_H
#define CALENDAR_INFOCOMMAND_H

#include "../Command.h"

class InfoCommand : public Command {
public:
    InfoCommand(InputUtility &inputUtility_, std::shared_ptr<Event> toEdit) :
            Command("info", "Prints out info about event", inputUtility_),
            target(std::move(toEdit)) {}

    InfoCommand(const InfoCommand &) = delete;

    std::vector<std::shared_ptr<Command>> executeAction(std::queue<std::string> &parameters) override {
        inputUtility.out << target->infoAll();
        return commands;
    };
private:
    std::shared_ptr<Event> target;
};

#endif //CALENDAR_INFOCOMMAND_H

/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 26.05.2020
 */

#ifndef CALENDAR_INFOCOMMAND_H
#define CALENDAR_INFOCOMMAND_H

#include "../Command.h"
#include "../../../Calendar/Event.h"

class InfoCommand : public Command {
public:
    InfoCommand(InputUtility &inputUtility_, shared_ptr<Event> toInfo) :
            Command("info", "Prints out info about event", inputUtility_),
            target(std::move(toInfo)) {}

    InfoCommand(const InfoCommand &) = delete;

    std::vector<std::shared_ptr<Command>> executeAction(const std::vector<std::string> &parameters) override {
        inputUtility.out <<
        return commands;
    };
private:
    shared_ptr<Event> target;
};

#endif //CALENDAR_INFOCOMMAND_H

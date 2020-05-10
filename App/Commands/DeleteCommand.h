/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 10.05.2020
 */

#ifndef CALENDAR_DELETECOMMAND_H
#define CALENDAR_DELETECOMMAND_H

#include "Command.h"

class DeleteCommand : public Command {
public:
    DeleteCommand(std::ostream &out_) : Command("delete", "Deletes an event", out_) {

    }

    std::vector<std::shared_ptr<Command>> executeAction(const std::vector<std::string> &parameters) override {
        out << "not implemented\n";
        return commands;
    };
};

#endif

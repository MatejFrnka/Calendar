/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 27.05.2020
 */

#ifndef CALENDAR_EDITCOMMAND_H
#define CALENDAR_EDITCOMMAND_H

#include "../../../Utility/InputUtility.h"
#include "../../../Calendar/Event.h"
#include "../Command.h"

class EditCommand : public Command {
public:
    EditCommand(InputUtility &inputUtility_, shared_ptr<Event> toDelete_) :
            Command("delete", "Deletes an event", inputUtility_),
            toDelete(std::move(toDelete_)) {};

    EditCommand(const EditCommand &) = delete;

    std::vector<std::shared_ptr<Command>> executeAction(const std::vector<std::string> &parameters) override {
        return commands;
    };
private:
    shared_ptr<Event> ;
};

#endif //CALENDAR_EDITCOMMAND_H

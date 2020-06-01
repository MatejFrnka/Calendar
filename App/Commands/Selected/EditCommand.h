/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 27.05.2020
 */

#ifndef CALENDAR_EDITCOMMAND_H
#define CALENDAR_EDITCOMMAND_H

#include "../../../Utility/InputUtility.h"
#include "../../../Calendar/Event.h"
#include "../Command.h"
#include "../../../Utility/Exceptions/EventNotEditableException.h"
#include "../CustomCommand.h"

class EditCommand : public Command {
public:
    EditCommand(InputUtility &inputUtility_, const shared_ptr<Event> &toEdit) : Command("edit", "Edits an event", inputUtility_), target(toEdit) {
        if (target && !target->getEditable()) {
            inputUtility.eventNotEditable();
            return;
        }
        CustomCommand personAdd("add", "Adds a new person", inputUtility,
                                [toEdit](std::queue<std::string> &params, CustomCommand &self) {
                                    shared_ptr<Person> person = make_shared<Person>(self.inputUtility.readString("Name", params),
                                                                                    self.inputUtility.readString("Surname", params));
                                    person->email = self.inputUtility.readString("Email", params, false);
                                    person->phone = self.inputUtility.readString("Phone", params, false);
                                    toEdit->addPerson(person);
                                    self.inputUtility.success();
                                    return std::vector<std::shared_ptr<Command>>();
                                });
        CustomCommand personList("list", "Shows all people", inputUtility,
                                 [toEdit](std::queue<std::string> &params, CustomCommand &self) {
                                     self.inputUtility.out << "List of people:" << endl;
                                     for (const auto &person : toEdit->getPeople())
                                         self.inputUtility.out << '\t' << *person << endl;
                                     return std::vector<std::shared_ptr<Command>>();
                                 });
        CustomCommand personRemove("delete", "Deletes person", inputUtility,
                                   [toEdit](std::queue<std::string> &params, CustomCommand &self) {
                                       size_t index = 0;
                                       const auto &people = toEdit->getPeople();
                                       for (const auto &person : people)
                                           self.inputUtility.out << "(" << index++ << ") " << *person << endl;
                                       toEdit->removePerson(people[self.inputUtility.readSelect("Select which to delete", people.size())]);
                                       self.inputUtility.success();
                                       return std::vector<std::shared_ptr<Command>>();
                                   });
        std::vector<std::shared_ptr<Command>> personCommands;
        personCommands.push_back(make_shared<CustomCommand>(personAdd));
        personCommands.push_back(make_shared<CustomCommand>(personList));
        personCommands.push_back(make_shared<CustomCommand>(personRemove));

        CustomCommand person("person", "Edits people in event", inputUtility,
                             [personCommands](std::queue<std::string> &params, CustomCommand &self) {
                                 return personCommands;
                             }, personCommands);

        commands.push_back(make_shared<CustomCommand>(person));

        CustomCommand location("location", "Changes location", inputUtility,
                               [toEdit](std::queue<std::string> &params, CustomCommand &self) {
                                   toEdit->setLocation(self.inputUtility.readString("Location", params, false));
                                   self.inputUtility.success();
                                   return std::vector<std::shared_ptr<Command>>();
                               });
        commands.push_back(make_shared<CustomCommand>(location));

        CustomCommand title("title", "Changes title", inputUtility,
                            [toEdit](std::queue<std::string> &params, CustomCommand &self) {
                                toEdit->setTitle(self.inputUtility.readString("Title", params, true));
                                self.inputUtility.success();
                                return std::vector<std::shared_ptr<Command>>();
                            });
        commands.push_back(make_shared<CustomCommand>(title));

        CustomCommand lock("lock", "Disables editing on event", inputUtility,
                           [toEdit](std::queue<std::string> &params, CustomCommand &self) {
                               self.inputUtility.out << "You will not be able to edit the event afterwards" << endl;
                               if (self.inputUtility.readBool("Are you sure you want to lock the event")) {
                                   toEdit->setEditable(false);
                                   self.inputUtility.success();
                               }
                               return std::vector<std::shared_ptr<Command>>();
                           });
        commands.push_back(make_shared<CustomCommand>(lock));
    }

    EditCommand(const EditCommand &) = delete;

    std::vector<std::shared_ptr<Command>> executeAction(std::queue<std::string> &parameters) override {
        return commands;
    };
private:
    shared_ptr<Event> target;
};

#endif //CALENDAR_EDITCOMMAND_H

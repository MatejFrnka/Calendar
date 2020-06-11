/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 27.05.2020
 */

#pragma once
#include "../../../Utility/InputUtility.h"
#include "../../../Calendar/Event.h"
#include "../Command.h"
#include "../../../Utility/Exceptions/EventNotEditableException.h"
#include "../CustomCommand.h"
#include "DurationCommand.h"
#include "MoveCommand.h"

class EditCommand : public Command {
public:
    /**
     * @throws EventNotEditableException when target event is not editable
     */
    EditCommand(InputUtility &inputUtility_, std::shared_ptr<Event> toEdit, EventManager &eventManager) : Command("edit", "Edits an event", inputUtility_), target(toEdit) {

        //Person edit commands
        CustomCommand personAdd("add", "Adds a new person", inputUtility,
                                [toEdit](std::queue<std::string> &params, CustomCommand &self) {
                                    std::shared_ptr<Person> person = std::make_shared<Person>(self.inputUtility.readString("Name", params),
                                                                                    self.inputUtility.readString("Surname", params));
                                    person->email = self.inputUtility.readString("Email", params, false);
                                    person->phone = self.inputUtility.readString("Phone", params, false);
                                    toEdit->addPerson(person);
                                    self.inputUtility.success();
                                    return std::vector<std::shared_ptr<Command>>();
                                });
        CustomCommand personList("list", "Shows all people", inputUtility,
                                 [toEdit](std::queue<std::string> &params, CustomCommand &self) {
                                     self.inputUtility.out << "List of people:" << std::endl;
                                     for (const auto &person : toEdit->getPeople())
                                         self.inputUtility.out << '\t' << *person << std::endl;
                                     return std::vector<std::shared_ptr<Command>>();
                                 });
        CustomCommand personRemove("delete", "Deletes person", inputUtility,
                                   [toEdit](std::queue<std::string> &params, CustomCommand &self) {
                                       size_t index = 0;
                                       const auto &people = toEdit->getPeople();
                                       for (const auto &person : people)
                                           self.inputUtility.out << "(" << index++ << ") " << *person << std::endl;
                                       toEdit->removePerson(people[self.inputUtility.readSelect("Select which to delete", people.size())]);
                                       self.inputUtility.success();
                                       return std::vector<std::shared_ptr<Command>>();
                                   });
        std::vector<std::shared_ptr<Command>> personCommands;
        personCommands.push_back(std::make_shared<CustomCommand>(personAdd));
        personCommands.push_back(std::make_shared<CustomCommand>(personList));
        personCommands.push_back(std::make_shared<CustomCommand>(personRemove));


        CustomCommand person("person", "Edits people in event", inputUtility,
                             [personCommands](std::queue<std::string> &params, CustomCommand &self) {
                                 return personCommands;
                             }, personCommands);

        commands.push_back(std::make_shared<CustomCommand>(person));

        //Location editing
        CustomCommand location("location", "Changes location", inputUtility,
                               [toEdit](std::queue<std::string> &params, CustomCommand &self) {
                                   toEdit->setLocation(self.inputUtility.readString("Location", params, false));
                                   self.inputUtility.success();
                                   return std::vector<std::shared_ptr<Command>>();
                               });
        commands.push_back(std::make_shared<CustomCommand>(location));
        //Title editing
        CustomCommand title("title", "Changes title", inputUtility,
                            [toEdit](std::queue<std::string> &params, CustomCommand &self) {
                                toEdit->setTitle(self.inputUtility.readString("Title", params, true));
                                self.inputUtility.success();
                                return std::vector<std::shared_ptr<Command>>();
                            });
        commands.push_back(std::make_shared<CustomCommand>(title));
        //IsEditable editing
        CustomCommand lock("lock", "Disables editing on event", inputUtility,
                           [toEdit](std::queue<std::string> &params, CustomCommand &self) {
                               self.inputUtility.out << "You will not be able to edit the event afterwards" << std::endl;
                               if (self.inputUtility.readBool("Are you sure you want to lock the event")) {
                                   toEdit->setEditable(false);
                                   self.inputUtility.success();
                               }
                               return std::vector<std::shared_ptr<Command>>();
                           });
        commands.push_back(std::make_shared<CustomCommand>(lock));

        commands.push_back(std::make_shared<DurationCommand>(inputUtility, toEdit, eventManager));
        commands.push_back(std::make_shared<MoveCommand>(inputUtility, toEdit, eventManager));

    }

    EditCommand(const EditCommand &) = delete;

    std::vector<std::shared_ptr<Command>> executeAction(std::queue<std::string> &parameters) override {
        if (target->getEditable())
            return commands;
        else
            inputUtility.eventNotEditable();
        return std::vector<std::shared_ptr<Command>>();
    };
private:
    std::shared_ptr<Event> target;
};


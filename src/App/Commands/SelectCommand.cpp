/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 26.05.2020
 */

#include "SelectCommand.h"
#include "CustomCommand.h"
#include "Selected/DeleteCommand.h"
#include "Selected/InfoCommand.h"
#include "Selected/EditCommand.h"
#include "../../Calendar/SingleEvent.h"

SelectCommand::SelectCommand(InputUtility &inputUtility, EventManager &eventManager_)
        : Command("select", "Selects an event", inputUtility, std::map<std::string, std::string>{{"date",  "Selects event by date"},
                                                                                                 {"title", "Selects event by title"},
                                                                                                 {"place", "Selects event by location"},
                                                                                                 {"all",   "Selects event by title and location"}}),
          eventManager(eventManager_) {
    commands.push_back(std::make_shared<DeleteCommand>(inputUtility, nullptr, eventManager));
    commands.push_back(std::make_shared<InfoCommand>(inputUtility, nullptr));
    commands.push_back(std::make_shared<EditCommand>(inputUtility, nullptr, eventManager));
}

std::vector<std::shared_ptr<Command>> SelectCommand::executeAction(std::queue<std::string> &parameters) {
    EventSet<std::shared_ptr<Event>> events;
    std::shared_ptr<Event> result;
    if (parameters.empty()) {
        inputUtility.noParameterFound();
        return std::vector<std::shared_ptr<Command>>();
    } else if (parameters.front() == "date") {
        parameters.pop();
        result = eventManager.findByStart(inputUtility.readDateTime("Start", parameters));
    } else if (parameters.front() == "title") {
        parameters.pop();
        events = eventManager.findByTitle(inputUtility.readString("Name", parameters));
    } else if (parameters.front() == "place") {
        parameters.pop();
        events = eventManager.findByAddress(inputUtility.readString("Address", parameters));
    } else if (parameters.front() == "all") {
        parameters.pop();
        auto addrEvents = eventManager.findByAddress(inputUtility.readString("Address", parameters));
        std::string title = inputUtility.readString("Title", parameters);
        for (const auto &ev : addrEvents) {
            if (ev->getTitle() == title)
                events.insert(ev);
        }
    } else {
        inputUtility.noParameterFound(parameters.front());
        parameters.pop();
        return std::vector<std::shared_ptr<Command>>();
    }
    size_t index = 0;
    // Selecting event in case of duplicates
    if (events.size() > 1) {
        inputUtility.out << "Multiple events found" << std::endl;
        for (const auto &event : events) {
            inputUtility.out << '(' << index << ") " << *event << std::endl;
            index++;
        }
        auto it = events.begin();
        std::advance(it, inputUtility.readSelect("Select which event", index));
        result = *it;
    } else if (events.size() == 1)
        result = *events.begin();

    if (result) {
        std::vector<std::shared_ptr<Command>> res;
        res.push_back(std::make_shared<DeleteCommand>(inputUtility, result, eventManager));
        res.push_back(std::make_shared<InfoCommand>(inputUtility, result));
        res.push_back(std::make_shared<EditCommand>(inputUtility, result, eventManager));
        inputUtility.out << "Event selected" << std::endl;
        return res;
    } else {
        inputUtility.out << "Event was not found" << std::endl;
    }
    return std::vector<std::shared_ptr<Command>>();
}



/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 26.05.2020
 */

#include "SelectCommand.h"
#include "CustomCommand.h"
#include "Selected/DeleteCommand.h"

SelectCommand::SelectCommand(InputUtility &inputUtility, EventManager &eventManager_)
        : Command("select", "Selects an event", inputUtility, std::map<std::string, std::string>{{"date",  "Selects event by date"},
                                                                                                 {"title", "Selects event by title"},
                                                                                                 {"place", "Selects date by location"}}),
          eventManager(eventManager_) {
    commands.push_back(make_shared<DeleteCommand>(inputUtility, nullptr, eventManager));
}

std::vector<std::shared_ptr<Command>> SelectCommand::executeAction(const std::vector<std::string> &parameters) {
    EventSet<shared_ptr<Event>> events;
    shared_ptr<Event> result;
    if (parameters.empty()) {
        inputUtility.noParameterFound();
        return std::vector<std::shared_ptr<Command>>();
    } else if (parameters[0] == "date") {
        result = eventManager.findByStart(inputUtility.readDateTime("Start", parameters.size() >= 2 ? parameters[1] : ""));
    } else if (parameters[0] == "title") {
        events = eventManager.findByTitle(inputUtility.readString("Name", parameters.size() >= 2 ? parameters[1] : ""));
    } else if (parameters[0] == "place") {
        events = eventManager.findByAddress(inputUtility.readString("Address", parameters.size() >= 2 ? parameters[1] : ""));
    } else {
        inputUtility.noParameterFound(parameters[0]);
        return std::vector<std::shared_ptr<Command>>();
    }
    size_t index = 0;
    if (events.size() > 1) {
        inputUtility.out << "Multiple events found" << std::endl;
        for (const auto &event : events) {
            cout << '(' << index << ')' << *event << std::endl;
            index++;
        }
        int res = 0;
        inputUtility.out << "Please select which event to select" << std::endl;
        while (true) {
            res = inputUtility.readNumber("Index");
            if (res >= 0 && res < index)
                break;
            inputUtility.out << "Given number does not match any option. Use number in (x) at the beginning of each line" << std::endl;
        }
        auto it = events.begin();
        std::advance(it, res);
        result = *it;
    } else if (events.size() == 1)
        result = *events.begin();

    if (result) {
        std::vector<std::shared_ptr<Command>> res;
        res.push_back(make_shared<DeleteCommand>(inputUtility, result, eventManager));
        inputUtility.out << "Event selected" << std::endl;
        return res;
    } else {
        inputUtility.out << "Event was not found" << std::endl;
    }
    return std::vector<std::shared_ptr<Command>>();
}



/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 10.05.2020
 */

#ifndef CALENDAR_APP_COMMANDS_CUSTOM_COMMAND
#define CALENDAR_APP_COMMANDS_CUSTOM_COMMAND

#include <functional>
#include <utility>
#include "Command.h"

using namespace std;

class CustomCommand : public Command {
public:
    CustomCommand(string name, string description, ostream &out, function<vector<shared_ptr<Command>> (vector<string>, CustomCommand &self)> function)
            : Command(move(name), move(description), out), fn(move(function)) {}

    vector<shared_ptr<Command>> executeAction(const vector<string> &parameters) override {
        return fn(parameters, *this);
    };
private:
    const function<vector<shared_ptr<Command>> (vector<string>, CustomCommand &self)> fn;
};

#endif

/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 10.05.2020
 */

#include "HelpCommand.h"

void HelpCommand::printCommandsRec(const std::vector<std::shared_ptr<Command>> &toPrint, int depth) const {
    depth++;
    for (const auto &it : toPrint) {
        for (int i = 1; i < depth; ++i) {
            if (i == depth - 1) {
                inputUtility.out << "|-";
            } else
                inputUtility.out << ". ";
        }
        inputUtility.out << it->name;

        for (auto param = it->params.begin(); param != it->params.end(); ++param) {
            if (param == it->params.begin())
                inputUtility.out << " <";
            else
                inputUtility.out << "|";
            inputUtility.out << param->first;
        }
        if (!it->params.empty())
            inputUtility.out << ">";
        inputUtility.out << "\t:" << it->description << std::endl;

        printCommandsRec(it->getSubCommands(), depth);
    }
}

std::vector<std::shared_ptr<Command>> HelpCommand::executeAction(std::queue<std::string> &parameters) {
    inputUtility.out << "cancel:\tCancels current action" << std::endl;
    inputUtility.out << "exit:\tSaves events and exits application" << std::endl;
    printCommandsRec(refCommands, 0);
    return refCommands;
}

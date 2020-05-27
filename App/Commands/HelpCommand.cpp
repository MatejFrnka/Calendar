/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 10.05.2020
 */

#include "HelpCommand.h"

void HelpCommand::printCommandsRec(const std::vector<std::shared_ptr<Command>> &toPrint, int depth) const {
    depth++;
    for (const auto &it : toPrint) {
        for (int i = 1; i < depth; ++i) {
            if (i == 1) {
                inputUtility.out << "|- ";
            } else
                inputUtility.out << "-- ";
        }
        inputUtility.out << *it << std::endl;
        for (const auto &param : it->params) {
            for (int i = 1; i < depth + 1; ++i) {
                if (i == 1) {
                    inputUtility.out << "|* ";
                } else
                    inputUtility.out << "** ";
                inputUtility.out << param.first << ":\t" << param.second << std::endl;
            }
        }
        printCommandsRec(it->getSubCommands(), depth);
    }
}

std::vector<std::shared_ptr<Command>> HelpCommand::executeAction(const std::vector<std::string> &parameters) {
    inputUtility.out << "cancel:\tCancels current action" << std::endl;
    printCommandsRec(refCommands, 0);
    return refCommands;
}
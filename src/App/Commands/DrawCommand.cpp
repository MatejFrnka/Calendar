/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 18.06.2020
 */

#include "DrawCommand.h"

DrawCommand::DrawCommand(InputUtility &inputUtility_, DrawManager &drawManager_) : Command("draw", "Draws events",
                                                                                           inputUtility_,
                                                                                           std::map<std::string, std::string>{
                                                                                                   {"\"\"",     "Draws at previous date at previous mode"},
                                                                                                   {"day",      "Changes draw mode to day"},
                                                                                                   {"week",     "Changes draw mode to week"},
                                                                                                   {"month",    "Changes draw mode to month"},
                                                                                                   {"set",      "Changes time to display"},
                                                                                                   {"next",     "Shows next date"},
                                                                                                   {"previous", "Shows previous date"}

                                                                                           }),
                                                                                   drawManager(drawManager_) {}

std::vector<std::shared_ptr<Command>> DrawCommand::executeAction(std::queue<std::string> &parameters) {
    if (!parameters.empty()) {
        auto parameter = parameters.front();
        parameters.pop();
        if (parameter == "month")
            drawManager.setMode(DrawManager::DrawMode::month);
        else if (parameter == "week")
            drawManager.setMode(DrawManager::DrawMode::week);
        else if (parameter == "day")
            drawManager.setMode(DrawManager::DrawMode::day);
        else if (parameter == "next")
            drawManager.next();
        else if (parameter == "previous")
            drawManager.previous();
        else if (parameter == "set") {
            time_t date = inputUtility.readDate("Date", parameters, true);
            drawManager.setDate(date);
        } else {
            inputUtility.noParameterFound(parameter);
            return std::vector<std::shared_ptr<Command>>();
        }
    }
    drawManager.draw();
    return std::vector<std::shared_ptr<Command>>();
}

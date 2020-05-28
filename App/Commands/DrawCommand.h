/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 20.05.2020
 */

#ifndef CALENDAR_DRAWCOMMAND_H
#define CALENDAR_DRAWCOMMAND_H

#include "Command.h"
#include "../../Draw/MonthDraw.h"
#include "../../Draw/DrawManager.h"

class DrawCommand : public Command {
public:
    DrawCommand(InputUtility &inputUtility_, DrawManager &drawManager_) :
            Command("draw", "Draws events",
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
            drawManager(drawManager_) {
    }

    std::vector<std::shared_ptr<Command>> executeAction(std::queue<std::string> &parameters) override {
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

private:
    DrawManager &drawManager;
};

#endif //CALENDAR_DRAWCOMMAND_H

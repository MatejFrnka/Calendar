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
    DrawCommand(InputUtility inputUtility_, DrawManager &drawManager_) : Command("draw", "Draws events", inputUtility_),
                                                                         drawManager(drawManager_) {
    }

    std::vector<std::shared_ptr<Command>> executeAction(const std::vector<std::string> &parameters) override {
        if (parameters.empty()) {
            drawManager.draw();
            return commands;
        }
        if (parameters[0] == "month")
            drawManager.setMode(DrawManager::DrawMode::month);
        if (parameters[0] == "week")
            drawManager.setMode(DrawManager::DrawMode::week);
        if (parameters[0] == "day")
            drawManager.setMode(DrawManager::DrawMode::day);
        drawManager.draw();
        return std::vector<std::shared_ptr<Command>>();
    }

private:
    DrawManager &drawManager;
};

#endif //CALENDAR_DRAWCOMMAND_H

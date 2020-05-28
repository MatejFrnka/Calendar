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
    DrawCommand(InputUtility &inputUtility_, DrawManager &drawManager_) : Command("draw", "Draws events", inputUtility_),
                                                                          drawManager(drawManager_) {
    }

    std::vector<std::shared_ptr<Command>> executeAction(std::queue<std::string> &parameters) override {
        if (!parameters.empty()) {
            if (parameters.front() == "month")
                drawManager.setMode(DrawManager::DrawMode::month);
            if (parameters.front() == "week")
                drawManager.setMode(DrawManager::DrawMode::week);
            if (parameters.front() == "day")
                drawManager.setMode(DrawManager::DrawMode::day);
            if (parameters.front() == "set") {
                time_t date = inputUtility.readDate("Date", parameters, true);
                drawManager.setDate(date);
            }
            if (parameters.front() == "next")
                drawManager.next();
            if (parameters.front() == "previous")
                drawManager.previous();

            parameters.pop();
        }
        drawManager.draw();
        return std::vector<std::shared_ptr<Command>>();
    }

private:
    DrawManager &drawManager;
};

#endif //CALENDAR_DRAWCOMMAND_H

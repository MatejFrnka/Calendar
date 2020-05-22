/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 20.05.2020
 */

#ifndef CALENDAR_DRAWCOMMAND_H
#define CALENDAR_DRAWCOMMAND_H

#include "Command.h"
#include "../../Draw/MonthDraw.h"

class DrawCommand : public Command {
public:
    DrawCommand(InputUtility &inputUtility_, EventManager &eventManager_) : Command("draw", "Draws events", inputUtility_), eventManager(eventManager_) {
        draw = std::unique_ptr<Draw>(new MonthDraw(inputUtility_.out, eventManager_));
    }

    std::vector<std::shared_ptr<Command>> executeAction(const std::vector<std::string> &parameters) override {
        MonthDraw monthDraw(inputUtility.out, eventManager);
        monthDraw.drawEvents(0);
        return std::vector<std::shared_ptr<Command>>();
    }

private:
    EventManager &eventManager;
    std::unique_ptr<Draw> draw;
};

#endif //CALENDAR_DRAWCOMMAND_H

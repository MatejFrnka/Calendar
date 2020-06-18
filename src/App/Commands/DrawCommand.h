/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 20.05.2020
 */

#pragma once

#include "Command.h"
#include "../../Draw/MonthDraw.h"
#include "../../Draw/DrawManager.h"

class DrawCommand : public Command {
public:
    DrawCommand(InputUtility &inputUtility_, DrawManager &drawManager_);

    std::vector<std::shared_ptr<Command>> executeAction(std::queue<std::string> &parameters) override;

private:
    DrawManager &drawManager;
};

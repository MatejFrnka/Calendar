/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 22.05.2020
 */

#include "DrawManager.h"
#include "MonthDraw.h"
#include "WeekDraw.h"
#include "DayDraw.h"

#include <utility>

DrawManager::DrawManager(EventManager &eventManager_, std::ostream &out_) : eventManager(eventManager_), out(out_) {
    drawUtility = std::make_unique<MonthDraw>(out_, eventManager_);
}

void DrawManager::draw() {
    drawUtility->drawEvents(time);
}

void DrawManager::setMode(DrawManager::DrawMode drawMode) {
    if (drawMode == DrawMode::month)
        drawUtility = std::make_unique<MonthDraw>(out, eventManager);
    if (drawMode == DrawMode::week)
        drawUtility = std::make_unique<WeekDraw>(out, eventManager);
    if (drawMode == DrawMode::day)
        drawUtility = std::make_unique<DayDraw>(out, eventManager);

}

/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 22.05.2020
 */

#include "DrawManager.h"
#include "MonthDraw.h"
#include "WeekDraw.h"
#include "DayDraw.h"
#include "../Utility/InputUtility.h"
#include <utility>

DrawManager::DrawManager(EventManager &eventManager_, std::ostream &out_) : eventManager(eventManager_), out(out_) {
    drawUtility = std::make_unique<MonthDraw>(out_, eventManager_);
    time_t now = InputUtility::getCurrentTime();
    time = *localtime(&now);
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

void DrawManager::next() {
    drawUtility->moveNext(time);
}

void DrawManager::previous() {
    drawUtility->movePrevious(time);
}

void DrawManager::setDate(time_t utcTime) {
    time = *localtime(&utcTime);
}

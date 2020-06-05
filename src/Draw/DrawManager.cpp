/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 22.05.2020
 */

#include "DrawManager.h"
#include "../Utility/InputUtility.h"

DrawManager::DrawManager(EventManager &eventManager_, std::ostream &out_) : eventManager(eventManager_), out(out_) {
    drawUtility = new MonthDraw(out_, eventManager_);
    time_t now = InputUtility::getCurrentTime();
    time = *localtime(&now);
}

void DrawManager::draw() {
    drawUtility->drawEvents(time);
}

void DrawManager::setMode(DrawManager::DrawMode drawMode) {
    delete drawUtility;
    if (drawMode == DrawMode::month)
        drawUtility = new MonthDraw(out, eventManager);
    if (drawMode == DrawMode::week)
        drawUtility = new WeekDraw(out, eventManager);
    if (drawMode == DrawMode::day)
        drawUtility = new DayDraw(out, eventManager);
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

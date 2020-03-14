//
// Created by Matej Frnka on 13.03.2020.
//

#include "DrawManager.h"

void DrawManager::draw(EventManager *eventManager) {
    drawMode->draw(eventManager, &displayTime);
}

DrawManager::DrawManager(Draw_a *drawMode_) {
    drawMode = drawMode_;
    displayTime = std::chrono::system_clock::to_time_t(chrono::system_clock::now());
}


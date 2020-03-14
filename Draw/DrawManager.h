//
// Created by Matej Frnka on 13.03.2020.
//

#ifndef CALENDAR_DRAWMANAGER_H
#define CALENDAR_DRAWMANAGER_H

#include "./../ProjectIncludes.h"
#include "./DrawIncludes.h"

class DrawManager {
public:


    DrawManager(Draw_a *drawMode_);

    void draw(EventManager *eventManager);

    Draw_a *drawMode = nullptr;
private:
    time_t displayTime;
};


#endif //CALENDAR_DRAWMANAGER_H

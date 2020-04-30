/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 29.04.2020
 */

#pragma once

#include <chrono>
#include "DrawModes/Draw_a.h"
#include "../Calendar/EventManager.h"

using namespace std;

class DrawManager {
public:


    DrawManager(Draw_a *drawMode_);

    void draw(EventManager *eventManager);

    Draw_a *drawMode = nullptr;

    ~DrawManager() {
        //if (drawMode)
        //    delete (drawMode);
    }

private:
    time_t displayTime;
};
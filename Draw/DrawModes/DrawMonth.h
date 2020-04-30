/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 29.04.2020
 */

#pragma once

#include <iostream>
#include "Draw_a.h"
#include "../../Calendar/EventManager.h"

using namespace std;

class DrawMonth : public Draw_a {
public:
    void draw(EventManager *eventManager, time_t *time) override;

private:

};

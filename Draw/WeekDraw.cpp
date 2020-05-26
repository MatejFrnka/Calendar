/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 22.05.2020
 */

#include "WeekDraw.h"

void WeekDraw::drawEvents(tm &time) {
    out << "week draw";
}

void WeekDraw::moveNext(tm &time) {
    time.tm_wday++;
    mktime(&time);
}

void WeekDraw::movePrevious(tm &time) {
    time.tm_wday--;
    mktime(&time);
}

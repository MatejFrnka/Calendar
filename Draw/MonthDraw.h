/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 10.05.2020
 */

#ifndef CALENDAR_DRAW_MONTH_DRAW
#define CALENDAR_DRAW_MONTH_DRAW


#include "Draw.h"
#include "../Utility/DatetimeUtility.h"

class MonthDraw : public Draw {
public:
    MonthDraw(std::ostream &out_, EventManager &eventManager_) : Draw(out_, eventManager_) {};

    void drawEvents(time_t time) override;
};

void MonthDraw::drawEvents(time_t time) {

    tm *displayTime = gmtime(&time);
    time_t startTime = DatetimeUtility::getStartRangeTime(DatetimeUtility::Month, displayTime);

    int weekDay = DatetimeUtility::convertWeekDay(displayTime->tm_wday);
    int numberOfDays = DatetimeUtility::getNumberOfDays(displayTime->tm_mon, displayTime->tm_year + 1900);



    //Draw week days
    for (const auto &dayOfWeek : DatetimeUtility::getWeekDays()) {
        cout << dayOfWeek << "\t";
    }
    cout << endl;
    //Draw empty fields
    for (int i = 0; i < weekDay; ++i) {
        cout << "\t";
    }
    //Draw days
    for (int i = 1; i <= numberOfDays; ++i) {
        displayTime->tm_mday = i + 1;
        time_t endTime = mktime(displayTime);
        auto events = eventManager.checkAvailability(startTime, endTime);
        if (events)
            cout << "|";
        //New line after sunday
        cout << i;
        if (events)
            cout << "|";
        cout << "\t";
        if ((i + weekDay) % 7 == 0)
            cout << '\n' << endl;
        startTime = endTime;
    }
}

#endif

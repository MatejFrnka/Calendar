/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 22.05.2020
 */


#include "DayDraw.h"

void DayDraw::drawEvents(time_t time) {
    //Get utc time_t of day start
    tm *displayTime = localtime(&time);
    time_t startTime = DatetimeUtility::getStartRangeTime(DatetimeUtility::Day, displayTime);
    //Get utc time_t of day end
    tm copy_displayTime = *displayTime;
    time_t endTime = DatetimeUtility::getEndRangeTime(DatetimeUtility::Day, &copy_displayTime);
    //Print displayed date
    out << displayTime->tm_mday << "-" << DatetimeUtility::getMonths()[displayTime->tm_mon] << "-" << displayTime->tm_year + 1900 << endl;

    auto events = eventManager.getEvents(startTime, endTime);
    auto eventIt = events.begin();

    int timeJump = 2;
    for (int i = 0; i <= 24; i += timeJump) {
        bool drawTimeLine = true;
        int latestHour = -1;
        while (eventIt != events.end() && (*eventIt)->getStartDateUtc() < startTime + 3600 * (i + timeJump)) {
            time_t eventStart = (*eventIt)->getStartDateUtc();
            tm *tm_eventStart = localtime(&eventStart);
            bool exactStart = tm_eventStart->tm_hour == i && tm_eventStart->tm_min == 0;
            //If event starts before day starts
            if ((*eventIt)->getStartDateUtc() < startTime)
                exactStart = true;
            //If event doesnt start exactly at drawn hour, draw hour divider line
            if (!exactStart && drawTimeLine) {
                drawLine(out, i);
                out << endl;
            }
            drawTimeLine = false;
            //Draw event start
            if ((*eventIt)->getStartDateUtc() < startTime) {
                //Draw event when started before day started
                mkTime(out, 0, 0);
                out << timeBorder << ' ' << customFill((*eventIt)->getTitle(), '.', '|', '|', width - 10) << ' ' << timeBorder << endl;
            } else {
                //Draw event start
                mkTime(out, tm_eventStart->tm_hour, tm_eventStart->tm_min);
                out << timeBorder << ' ' << customFill((*eventIt)->getTitle(), '=', '|', '|', width - 10) << ' ' << timeBorder << endl;
            }

            //Get event end
            delete tm_eventStart;
            time_t eventEnd = (*eventIt)->getEndDateUtc();
            tm *tm_eventEnd = localtime(&eventEnd);
            //Draw body
            for (int j = i + timeJump; j < tm_eventEnd->tm_hour; j += timeJump) {
                mkTime(out, j, 0);
                out << timeBorder << ' ' << customFill("", ' ', '|', '|', width - 10) << ' ' << timeBorder << endl;

            }
            //Draw event end
            if (eventEnd > endTime) {
                mkTime(out, 24, 0);
                out << timeBorder << ' ' << customFill("", '.', '|', '|', width - 10) << ' ' << timeBorder << endl;
                latestHour = 25;
            } else {
                mkTime(out, tm_eventEnd->tm_hour, tm_eventEnd->tm_min);
                out << timeBorder << ' ' << customFill("", '_', '|', '|', width - 10) << ' ' << timeBorder << endl;
                latestHour = tm_eventEnd->tm_hour;
            }
            eventIt++;
            delete tm_eventEnd;
        }
        while (latestHour >= i + timeJump)
            i += timeJump;
        if (drawTimeLine) {
            drawLine(out, i);
            out << endl;
        }
    }
}

void DayDraw::drawLine(ostream &o, int hour) {
    mkTime(o, hour, 0);
    o << timeBorder << setfill(timeBreak) << setw(width - 6) << timeBorder;
}

void DayDraw::mkTime(ostream &o, int hour, int minute) {
    o << setfill('0') << setw(2) << (hour) << ":" << setw(2) << minute << " ";
}

string DayDraw::customFill(const string &body, char fillChar, char lborder, char rborder, int customWidth) const {
    ostringstream ss;
    ss << setfill(fillChar) << lborder << fillChar << (body.empty() ? fillChar : ' ') << (body.length() > customWidth - 6 ? body.substr(0, customWidth - 6) + ".." : body)
       << (body.empty() ? fillChar : ' ')
       << setw(customWidth - 3 - static_cast<int>(body.length())) << rborder;
    return ss.str();
}
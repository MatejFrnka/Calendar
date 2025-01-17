/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 22.05.2020
 */


#include "DayDraw.h"
#include "../Calendar/SingleEvent.h"

void DayDraw::drawEvents(tm &time) {
    time_t startTime = DatetimeUtility::getStartRangeTime(DatetimeUtility::Day, &time);
    //Print displayed date
    out << DatetimeUtility::drawDate(time, DatetimeUtility::RangeTime::Day) << std::endl;
    //Get utc time_t of day end
    time_t endTime = DatetimeUtility::getEndRangeTime(DatetimeUtility::Day, &time);
    auto events = eventManager.getEvents(startTime, endTime);
    auto eventIt = events.begin();
    //loop through hours
    for (int i = 0; i <= 24; i += timeJump) {
        bool drawTimeLine = true;
        int latestHour = -1;
        while (eventIt != events.end() && (*eventIt)->getStartDateUtc() <= startTime + 3600 * i) {
            drawTimeLine = false;
            //Get event start
            time_t eventStart = (*eventIt)->getStartDateUtc();
            tm tm_eventStart = *localtime(&eventStart);
            int hourStart = eventStart < startTime ? -1 : tm_eventStart.tm_hour;
            int minuteStart = tm_eventStart.tm_min;
            //Get event end
            time_t eventEnd = (*eventIt)->getEndDateUtc();
            tm tm_eventEnd = *localtime(&eventEnd);
            latestHour = eventEnd >= endTime ? 25 : tm_eventEnd.tm_hour;
            int minuteEnd = tm_eventEnd.tm_min;
            //draw the event
            drawEvent(**eventIt, hourStart, minuteStart, latestHour, minuteEnd);
            //move to next event
            eventIt++;
        }
        //move i to end after event
        while (latestHour >= i + timeJump)
            i += timeJump;
        if (drawTimeLine) {
            drawLine(out, i);
            out << std::endl;
        }
    }
    movePrevious(time);
}

void DayDraw::drawEvent(const Event &event, int hourStart, int minuteStart, int hourEnd, int minuteEnd) const {
    drawEventStart(event, hourStart, minuteStart);
    int j = hourStart + timeJump;
    if (hourStart > 0 && hourEnd < 25)
        j -= hourStart % timeJump;
    for (; j < hourEnd; j += timeJump) {
        mkTime(out, j, 0);
        out << timeBorder << ' ' << customFill("", ' ', '|', '|', width - 10) << ' ' << timeBorder << std::endl;
    }
    drawEventEnd(event, hourEnd, minuteEnd);
}

void DayDraw::drawEventStart(const Event &event, int hourStart, int minuteStart) const {
    if (hourStart < 0) {
        //Draw event when started before day started
        mkTime(out, 0, 0);
        out << timeBorder << ' ' << customFill(event.getTitle(), '.', '|', '|', width - 10) << ' ' << timeBorder << std::endl;
    } else {
        //Draw event start
        mkTime(out, hourStart, minuteStart);
        out << timeBorder << ' ' << customFill(event.getTitle(), '=', '|', '|', width - 10) << ' ' << timeBorder << std::endl;
    }
}

void DayDraw::drawEventEnd(const Event &event, int hourEnd, int minuteEnd) const {
    if (hourEnd > 24) { // Event ends after the day
        mkTime(out, 24, 0);
        out << timeBorder << ' ' << customFill("", '.', '|', '|', width - 10) << ' ' << timeBorder << std::endl;
    } else { // Event ends during the day
        mkTime(out, hourEnd, minuteEnd);
        out << timeBorder << ' ' << customFill("", '_', '|', '|', width - 10) << ' ' << timeBorder << std::endl;
    }
}

void DayDraw::drawLine(std::ostream &o, int hour) const {
    mkTime(o, hour, 0);
    o << timeBorder << std::setfill(timeBreak) << std::setw(width - 6) << timeBorder;
}

void DayDraw::mkTime(std::ostream &o, int hour, int minute) const {
    o << std::setfill('0') << std::setw(2) << (hour) << ":" << std::setw(2) << minute << " ";
}

std::string DayDraw::customFill(const std::string &body, char fillChar, char lborder, char rborder, unsigned int customWidth) const {
    std::ostringstream ss;
    ss << std::setfill(fillChar) << lborder << fillChar << (body.empty() ? fillChar : ' ') << (body.length() > customWidth - 6 ? body.substr(0, customWidth - 6) + ".." : body)
       << (body.empty() ? fillChar : ' ')
       << std::setw(customWidth - 3 - static_cast<int>(body.length())) << rborder;
    return ss.str();
}

void DayDraw::moveNext(tm &time) const {
    time.tm_mday++;
}

void DayDraw::movePrevious(tm &time) const {
    time.tm_mday--;
}

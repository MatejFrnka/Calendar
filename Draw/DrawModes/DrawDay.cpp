/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 29.04.2020
 */
/*
#include "DrawDay.h"

void DrawDay::draw(EventManager *eventManager, time_t *time) {
    tm *tmTime = gmtime(time);
    time_t startTime = calendarUtility.getStartRangeTime(calendarUtility.Day, tmTime);
    string weekDay = calendarUtility.weekDays[calendarUtility.convertWeekDay(tmTime->tm_wday)];
    time_t endTime = calendarUtility.getEndRangeTime(calendarUtility.Day, tmTime);

    //vector<Event *> *events = eventManager->getEvents(startTime, endTime);
    vector<Event *> *events = nullptr;
    cout << weekDay << endl;
    cout << drawLine(dayWidth) << endl;
    Event *currentlyDrawing = nullptr;
    for (int i = 0; i < 24; ++i) {
        for (int j = 0; j < 2; ++j) {
            Event *tmp = getCurrent(events, i, j * 30);

            if (j == 0) {
                cout << std::setw(2) << i << ":00  ";

            } else {
                cout << drawLine(6);
            }

            if (tmp != nullptr) {
                if (tmp == currentlyDrawing) {
                    cout << drawCalendarBlock(dayWidth - 8, "", CalendarType::Center);
                } else {
                    cout << drawCalendarBlock(dayWidth - 8, tmp->title, CalendarType::Start);
                }
            } else if (j == 1) {
                cout << drawLine(dayWidth - 8);
            }
            if (j == 1)
                cout << drawLine(2);
            cout << endl;
            currentlyDrawing = tmp;
        }
    }
}

string DrawDay::drawLine(int width) {
    string result = "";
    for (int i = 0; i < width; ++i) {
        result += "_";
    }
    return result;
}

Event *DrawDay::getCurrent(vector<Event *> *events, int hour, int minute) {
    for (auto event : *events) {
        if (event->getHour(true) >= hour && event->getHour(false) <= hour) {
            if (event->getMinute(true) >= minute && event->getMinute(false) <= minute)
                return event;
        }
    }
    return nullptr;
}

string DrawDay::customFill(int width, string *body, string fillChar, string lborder, string rborder) {
    string result = "";
    result += lborder;
    for (int i = 0; i < width - 4; ++i) {
        if (body != nullptr && *body != "" && body->length() > i) {
            if (body->length() > width - 5 && i > width - 7)
                result += ".";
            else
                result += (*body)[i];
        } else
            result += fillChar;
    }
    result += rborder;
    return result;
}

string DrawDay::drawCalendarBlock(int width, string body, CalendarType type) {
    if (type == CalendarType::Start) {
        return customFill(width, &body, "═", "╔", "╗");
    }
    if (type == CalendarType::Center) {
        return customFill(width, &body, " ", "║", "║");
    }
    if (type == CalendarType::End) {
        return customFill(width, &body, "═", "╚", "╝");
    }
    return "";
}
*/
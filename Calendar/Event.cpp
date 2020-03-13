//
// Created by Matej Frnka on 13.03.2020.
//

#include "Event.h"

bool Event::isInRange(time_t start, time_t end) {
    return ((startDateUtc > start && startDateUtc < end)
            || (endDateUtc > start && endDateUtc < end)
            || (startDateUtc < start && endDateUtc > end));
}

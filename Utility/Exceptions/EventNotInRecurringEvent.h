/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 02.05.2020
 */

#ifndef CALENDAR_UTILITY_EXCEPTIONS_EVENT_NOT_IN_RECURRING_EVENT
#define CALENDAR_UTILITY_EXCEPTIONS_EVENT_NOT_IN_RECURRING_EVENT

#include <exception>

/**
 * Used when trying to generate event from recurring event but the generated event does not mach recurring pattern of the recurring event
 */
class EventNotInRecurringEvent : std::exception {

};

#endif
/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 03.05.2020
 */

#ifndef CALENDAR_UTILITY_EVENT_SET
#define CALENDAR_UTILITY_EVENT_SET

#include <set>

template<typename T>
struct compare_reference {
    bool operator()(const T lhs, const T rhs) {
        return *lhs < *rhs;
    }
};

template<typename T>
class EventSet : public std::set<T, compare_reference<T>> {

};

#endif
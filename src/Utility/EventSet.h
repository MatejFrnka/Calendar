/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 03.05.2020
 */

#pragma once
#include <set>

template<typename T>
struct compare_reference {
    bool operator()(const T lhs, const T rhs) {
        return *lhs < *rhs;
    }
};

template<typename T>
using EventSet = std::set<T, compare_reference<T>>;

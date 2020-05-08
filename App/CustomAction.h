/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 06.05.2020
 */

#ifndef CALENDAR_APP_CUSTOM_ACTION
#define CALENDAR_APP_CUSTOM_ACTION

#include "Action.h"

template<typename function>
class CustomAction : Action {
public:
    CustomAction() = delete;

    CustomAction(function fn);

    outcome executeAction() override;

private:
    function fn;
};

#endif
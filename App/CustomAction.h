/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 06.05.2020
 */

#pragma once


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


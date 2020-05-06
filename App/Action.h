/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 06.05.2020
 */

#pragma once

struct Action {
public:
    enum outcome{
        Success,
        Failed
    };
    Action() = delete;

    virtual outcome executeAction() = 0;
};



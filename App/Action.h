/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 06.05.2020
 */

#ifndef CALENDAR_APP_ACTION
#define CALENDAR_APP_ACTION

struct Action {
public:
    enum outcome {
        Success,
        Failed
    };

    Action() = delete;

    virtual outcome executeAction() = 0;
};

#endif

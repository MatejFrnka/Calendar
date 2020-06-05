/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 03.06.2020
 */

#include "CalendarApp.h"
#include "Calendar/EventManager.h"
#include "Utility/FileUtility.h"
#include "App/Interface.h"

void CalendarApp::start() const {
    cout << "Calendar running" << endl;
    EventManager ev;
    if (!load(ev))
        cout << "Calendar failed to load events" << endl;
    Interface inteface(cin, cout, ev);
    inteface.start();
    cout << "Saving events" << endl;
    if (!save(ev))
        cout << "Failed to save events. Please check program has read-write permissions in its location." << endl;
    else
        cout << "Events saved" << endl;
}

bool CalendarApp::load(EventManager &eventManager) const {
    auto data = FileUtility::readData();
    size_t failedLoads = 0;
    for (const auto &f:data) {
        try {
            if (!eventManager.addEvent(f))
                failedLoads++;
        }
        catch (InvalidEventSequenceException &e) {
            failedLoads++;
        }
    }
    if (failedLoads > 0)
        cout << "Failed to load " << failedLoads << " events" << endl;
    return true;
}

bool CalendarApp::save(EventManager &eventManager) const {
    return FileUtility::saveData(eventManager.exportEvents());
}

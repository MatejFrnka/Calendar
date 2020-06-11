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
    if (!FileUtility::load(ev, cout))
        cout << "Calendar failed to load events" << endl;
    Interface inteface(cin, cout, ev);
    inteface.start();
    cout << "Saving events" << endl;
    if (!save(ev))
        cout << "Failed to save events. Please check program has read-write permissions in its location." << endl;
    else
        cout << "Events saved" << endl;
}

bool CalendarApp::save(EventManager &eventManager) const {
    return FileUtility::saveData(eventManager.exportEvents());
}

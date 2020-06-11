/**
 * @author: Matej Frnka <frnkamat@fit.cvut.cz>
 * @date: 03.06.2020
 */

#include "CalendarApp.h"
#include "Calendar/EventManager.h"
#include "Utility/FileUtility.h"
#include "App/Interface.h"

void CalendarApp::start() const {
    std::cout << "Calendar running" << std::endl;
    EventManager ev;
    if (!FileUtility::load(ev, std::cout))
        std::cout << "Calendar failed to load events" << std::endl;
    Interface inteface(std::cin, std::cout, ev);
    inteface.start();
    std::cout << "Saving events" << std::endl;
    if (!save(ev))
        std::cout << "Failed to save events. Please check program has read-write permissions in its location." << std::endl;
    else
        std::cout << "Events saved" << std::endl;
}

bool CalendarApp::save(EventManager &eventManager) const {
    return FileUtility::saveData(eventManager.exportEvents());
}

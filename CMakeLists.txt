cmake_minimum_required(VERSION 3.15)
project(Calendar)

set(CMAKE_CXX_STANDARD 14)

add_executable(Calendar main.cpp Calendar/Event.cpp Calendar/Event.h ProjectIncludes.h Calendar/SingleEvent.cpp Calendar/SingleEvent.h Calendar/RecurringEvent.cpp Calendar/RecurringEvent.h Calendar/EventManager.cpp Calendar/EventManager.h Calendar/RecurringItemEvent.cpp Calendar/RecurringItemEvent.h Calendar/CalendarIncludes.h Draw/DrawIncludes.h Draw/DrawManager.cpp Draw/DrawManager.h Draw/DrawModes/Draw_a.cpp Draw/DrawModes/Draw_a.h Draw/DrawModes/DrawMonth.cpp Draw/DrawModes/DrawMonth.h Draw/CalendarUtility.cpp Draw/CalendarUtility.h)
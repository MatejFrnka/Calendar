cmake_minimum_required(VERSION 3.15)
project(Calendar)

set(CMAKE_CXX_STANDARD 14)

set(GCC_COVERAGE_COMPILE_FLAGS "-pedantic -fsanitize=address")

add_executable(Calendar main.cpp Calendar/Event.cpp Calendar/Event.h Calendar/SingleEvent.cpp Calendar/SingleEvent.h Calendar/RecurringEvent.cpp Calendar/RecurringEvent.h Calendar/EventManager.cpp Calendar/EventManager.h Calendar/RecurringItemEvent.cpp Calendar/RecurringItemEvent.h Utility/Exceptions/EventNotEditable.cpp Utility/Exceptions/EventNotEditable.h Utility/Exceptions/EventNotInRecurringEvent.cpp Utility/Exceptions/EventNotInRecurringEvent.h Utility/InheritableSharedFromThis.h Utility/EventSet.cpp Utility/EventSet.h Utility/EventsIterator.cpp Utility/EventsIterator.h App/Action.cpp App/Action.h)

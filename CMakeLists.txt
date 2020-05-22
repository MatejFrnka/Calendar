cmake_minimum_required(VERSION 3.15)
project(Calendar)

set(CMAKE_CXX_STANDARD 14)

set(GCC_COVERAGE_COMPILE_FLAGS "-pedantic -fsanitize=address")

add_executable(Calendar main.cpp Calendar/Event.cpp Calendar/Event.h Calendar/SingleEvent.cpp Calendar/SingleEvent.h Calendar/RecurringEvent.cpp Calendar/RecurringEvent.h Calendar/EventManager.cpp Calendar/EventManager.h Calendar/RecurringItemEvent.cpp Calendar/RecurringItemEvent.h Utility/Exceptions/EventNotEditable.cpp Utility/Exceptions/EventNotEditable.h Utility/Exceptions/EventNotInRecurringEvent.cpp Utility/Exceptions/EventNotInRecurringEvent.h Utility/InheritableSharedFromThis.h Utility/EventSet.h Utility/EventsIterator.cpp Utility/EventsIterator.h App/Commands/Command.h App/Interface.cpp App/Interface.h Draw/Draw.h Utility/EventSet.h Utility/EventSet.h App/Commands/HelpCommand.h Utility/InputUtility.cpp Utility/InputUtility.h App/Commands/CustomCommand.h App/Commands/DeleteCommand.h Draw/DayDraw.h Draw/WeekDraw.h Draw/MonthDraw.h App/Commands/CreateCommand.cpp App/Commands/HelpCommand.cpp Utility/DatetimeUtility.cpp Utility/DatetimeUtility.h App/Commands/DrawCommand.h Draw/DrawManager.cpp Draw/DrawManager.h Draw/MonthDraw.cpp Draw/WeekDraw.cpp Draw/DrawDay.cpp Utility/Exceptions/CommandNotFound.cpp Utility/Exceptions/CommandNotFound.h)

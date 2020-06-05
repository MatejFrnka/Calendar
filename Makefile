CC=g++
CFLAGS=-std=c++14 -Wall -pedantic -Wno-long-long

LIST=src/main src/Calendar/Event src/Calendar/SingleEvent src/Calendar/RecurringEvent src/Calendar/EventManager src/Calendar/RecurringItemEvent src/App/Interface src/Utility/InputUtility src/App/Commands/CreateCommand src/App/Commands/HelpCommand src/Utility/DatetimeUtility src/Draw/DrawManager src/Draw/MonthDraw src/Draw/WeekDraw src/Draw/DayDraw src/App/Commands/SelectCommand src/CalendarApp

all: $(LIST)
	$(CC) $(CFLAGS) $(LIST)

%:	%.cpp
	$(CC) $(CFLAGS) $@.cpp -c -o $@

clean:
	rm $(LIST)
CC=g++
CFLAGS=-std=c++14 -Wall -pedantic -Wno-long-long

LIST=main Calendar/Event Calendar/SingleEvent Calendar/RecurringEvent Calendar/EventManager Calendar/RecurringItemEvent App/Interface Utility/InputUtility App/Commands/CreateCommand App/Commands/HelpCommand Utility/DatetimeUtility Draw/DrawManager Draw/MonthDraw Draw/WeekDraw Draw/DayDraw App/Commands/SelectCommand CalendarApp

all: $(LIST)
	$(CC) $(CFLAGS) $(LIST)

%:	%.cpp
	$(CC) $(CFLAGS) $@.cpp -c -o $@

clean:
	rm $(LIST)
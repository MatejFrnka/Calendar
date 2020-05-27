CC=g++
CFLAGS=-std=c++14 -Wall -pedantic -Wno-long-long

LIST=main Calendar/Event Calendar/SingleEvent Calendar/RecurringEvent Calendar/EventManager Calendar/RecurringItemEvent Utility/Exceptions/EventNotEditable Utility/Exceptions/EventNotInRecurringEventException Utility/EventsIterator App/Interface Draw/Draw Utility/InputUtility App/Commands/CreateCommand App/Commands/HelpCommand

all: $(LIST)
	$(CC) $(CFLAGS) $(LIST)

%:	%.cpp
	$(CC) $(CFLAGS) $@.cpp -c -o $@

clean:
	rm $(LIST)
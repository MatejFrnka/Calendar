CC=g++
CFLAGS=-std=c++14 -Wall -pedantic -Wno-long-long

LIST=main test

all: $(LIST)
	$(CC) $(LIST)

%:	%.cpp
	$(CC) $(CFLAGS) $@.cpp -c -o $@

clean:
	rm $(LIST)
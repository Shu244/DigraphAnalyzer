CC=g++
CFLAGS=-std=c++11 -pedantic -Wall -Wextra -g

digraphAnalyzer: digraphAnalyzer.o
	$(CC) digraphAnalyzer.o -o digraphAnalyzer

digraphAnalyzer.o: digraphAnalyzer.cpp
	$(CC) $(CFLAGS) -c digraphAnalyzer.cpp

clean:
	rm -f *.o digraphAnalyzer

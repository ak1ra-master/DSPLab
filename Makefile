CC=clang++
CXXFLAGS=-c -Wall -O0

all: start

start: main.o
	$(CC) main.o -o start

main.o: main.cpp
	$(CC) $(CXXFLAGS) main.cpp

clean:
	rm -rf *.o start

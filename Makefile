CC=g++
CFLAGS=-c -Wall -std=c++11
LDFLAGS=
SOURCES=$(wildcard *.cpp)
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=$(SOURCES:.cpp=)

all: $(EXECUTABLE)

%.o: %.cpp
	$(CC) $(CFLAGS) $^ -o $@

$(EXECUTABLE): % : %.o
	$(CC) $(LDFLAGS) $^ -o $@

.PHONY:	clean
clean:
	rm -f $(EXECUTABLE) *.o
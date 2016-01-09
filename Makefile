CC=g++
CFLAGS=-c -Wall --std=c++11
LDFLAGS=
SOURCES=main.cc run.cc population.cc agent.cc
OBJECTS=$(SOURCES:.cc=.o)
EXECUTABLE=test

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cc.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm $(OBJECTS)

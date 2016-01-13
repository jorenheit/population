CC=g++
CFLAGS=-c -Wall --std=c++11 -O2 -pg
LDFLAGS=-lm -pg
SOURCES=main.cc \
run.cc \
population.cc \
agent.cc \
coordinate.cc \
basicpolicies.cc
OBJECTS=$(SOURCES:.cc=.o)
EXECUTABLE=test

all: $(SOURCES) $(EXECUTABLE)

depend: .depend

.depend: $(SOURCES)
	rm -f ./.depend
	$(CC) $(CFLAGS) -MM $^ >  ./.depend;

include .depend

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cc.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm $(OBJECTS) .depend

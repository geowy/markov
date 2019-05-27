TARGET = markov
OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))
HEADERS = $(wildcard *.h)

%.o: %.c $(HEADERS)
	cc -Wall -c $< -o $@

$(TARGET): $(OBJECTS)
	cc $(OBJECTS) -Wall -o $@

.PHONY: default all clean

default: $(TARGET)

all: $(TARGET)

clean:
	rm -f *.o
	rm -f $(TARGET)

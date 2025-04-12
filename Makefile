CC = g++
CFLAGS = -Wall -std=c++20

BOTAN_PREFIX ?= /opt/homebrew/Cellar/botan/3.7.1
CFLAGS += -I$(BOTAN_PREFIX)/include/botan-3
LDFLAGS = -L$(BOTAN_PREFIX)/lib -lbotan-3

OBJS = main.o goldwasser-micali.o
EXECUTABLE = goldwasser-micali

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

run: $(EXECUTABLE)
	./$(EXECUTABLE)

clean:
	rm -f $(EXECUTABLE) $(OBJS)

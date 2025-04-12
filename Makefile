CC = g++
CFLAGS = -Wall -std=c++20 -I/opt/homebrew/Cellar/botan/3.7.1/include/botan-3
LDFLAGS = -L/opt/homebrew/Cellar/botan/3.7.1/lib -lbotan-3
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

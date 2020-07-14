# Add additional compiler flags here
CFLAGS=-O0

all: main
main: main.c peanoM.S
	$(CC) $(CFLAGS)  -no-pie  -o $@ $^ -lm
clean:
	rm -f main


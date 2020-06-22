# Add additional compiler flags here
CFLAGS=-O0

all: main
main: main.c curveM.S
	$(CC) $(CFLAGS) -no-pie -o $@ $^
clean:
	rm -f main


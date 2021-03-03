# Add additional compiler flags here
CFLAGS=-O2 -g
all: main 
main: main.c peanoM.S
	$(CC) $(CFLAGS)  -no-pie -o   $@ $^ -lm
clean:
	rm -f main

#-no-pie : non representable section output

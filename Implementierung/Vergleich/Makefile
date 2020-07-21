# Add additional compiler flags here
CFLAGS=-O2 -g
LDLIBS = -lm
all: cimp 
main: cimp.c peano.c
	$(CC) $(CFLAGS)   -o $@
clean:
	rm -f main

#-no-pie : non representable section output

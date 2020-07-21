# Add additional compiler flags here
CFLAGS=-O2 -g
LDLIBS = -lm
all: cimp 
main: cimp.c peano.h
	$(CC) $(CFLAGS)   -o $@
clean:
	rm -f cimp


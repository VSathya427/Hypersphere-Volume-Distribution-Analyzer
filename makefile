CC=gcc
CFLAGS=-Wall -Wextra -pedantic -g 
PROGS = ball_samp-cpu
OBJ = ball_samp-cpu.o

all: clean $(PROGS) 

%.o: %.c 
	$(CC) -c -o $@ $< $(CFLAGS)

ball_samp-cpu: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f *.o *.d *~ $(PROGS)
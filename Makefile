CC = gcc
CFLAGS = -Wall -std=c89 -O2 -I. `pkg-config --cflags raylib`
LDFLAGS = `pkg-config --libs raylib` -lm

SRCS = main.c audio.c wave.c filters.c ui.c
OBJS = $(SRCS:.c=.o)

wavelab: $(OBJS)
	$(CC) $(CFLAGS) -o wavelab $(OBJS) $(LDFLAGS)

clean:
	rm -f *.o wavelab

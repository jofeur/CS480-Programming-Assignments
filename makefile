CC=gcc
CFLAGS=-pthread

bots: Thread.c
    $(CC) $(CFLAGS) -o bots Thread.c

clean:
    rm -f bots

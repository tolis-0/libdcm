CC = gcc
CFLAGS = -g -O2 -Wall -Wextra

SOURCEF = $(wildcard *.c)
HEADERF = $(wildcard *.h)
OBJECTF = $(patsubst %.c,%.o,$(SOURCEF))

.PHONY: clean

all: $(OBJECTF)

$(OBJECTF):
	$(CC) $(CFLAGS) -c *.c

clean:
	rm -f *.o

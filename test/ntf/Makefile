CC = gcc
CFLAGS = -g3 -Wall -Wextra
LIBFLAGS = -lm -ldcm -lgmp

SOURCEF = $(wildcard *.c)
EXEF = $(patsubst %.c,%,$(SOURCEF))
TESTLIB = ../dctest.c

.PHONY: clean test

all: $(EXEF)

$(EXEF): %: %.c
	$(CC) $(CFLAGS) -o $@ $< $(TESTLIB) $(LIBFLAGS)

clean:
	find . -type f -executable -delete

test:
	find . -type f -executable -name '*test*' -exec {} \;

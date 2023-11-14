CC = gcc
CFLAGS = -g -O2 -Wall -Wextra
ARCHITECTURE = $(shell uname -m)

ifeq ($(ARCHITECTURE),x86_64)
	SOURCEF = $(filter-out montgomery.c, $(wildcard *.c))
else
	SOURCEF = $(wildcard *.c)
endif

HEADERF = $(wildcard *.h)
OBJECTF = $(patsubst %.c,%.o,$(SOURCEF))

.PHONY: clean

all: $(OBJECTF)
ifeq ($(ARCHITECTURE),x86_64)
	cd x86_64 && make
	cp x86_64/*.o .
endif

$(OBJECTF):
	$(CC) $(CFLAGS) -c *.c

clean:
	rm -f *.o
ifeq ($(ARCHITECTURE),x86_64)
	cd x86_64 && make clean
	cp x86_64/*.o .
endif

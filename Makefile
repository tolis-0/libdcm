CC=gcc
CFLAGS=-g -Wall -Wextra
LFLAGS=-g -shared

SOURCEF=num_theory.c sequences.c
OBJECTF=num_theory.o sequences.o
HEADERF=dcmath.h num_theory.h sequences.h
LIBF=/usr/local/lib/libdcm.so

SOURCEDIR=./src
LIBDIR=/usr/local/lib/libdcm/
INCLUDEDIR=/usr/local/include/

all: copy compile link include

include:
	cp $(HEADERF) $(INCLUDEDIR)

link:
	$(CC) $(LFLAGS) -o $(LIBF) $(OBJECTF)

compile:
	$(CC) $(CFLAGS) -c $(SOURCEF)

copy:
	cp $(WORKDIR)*.c $(WORKDIR)*.h $(LIBDIR)

clean:
	rm *.o $(LIBF)

cleanall:
	rm *.o *.c *.h $(LIBF)
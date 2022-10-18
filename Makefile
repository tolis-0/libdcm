CC=gcc
CFLAGS=-g -Wall -Wextra
LFLAGS=-g -shared

SOURCEDIR=./src/
LIBDIR=/usr/local/lib/libdcm/
INCLUDEDIR=/usr/local/include/

SOURCEF=$(foreach D, $(SOURCEDIR), $(wildcard $(D)/*.c))
HEADERF=$(foreach D, $(SOURCEDIR), $(wildcard $(D)/*.h))
OBJECTF=$(patsubst %.c,%.o,$(SOURCEF))
LIBF=/usr/local/lib/libdcm.so

all: copy compile link include clean

copy:	
	mkdir -p $(LIBDIR); \
	cp $(SOURCEF) $(HEADERF) $(LIBDIR)

compile:
	cd $(LIBDIR); \
	$(CC) $(CFLAGS) -c *.c

link:
	cd $(LIBDIR); \
	$(CC) $(LFLAGS) -o $(LIBF) *.o

include:
	cp $(HEADERF) $(INCLUDEDIR)

clean:
	rm $(LIBDIR)*.o $(LIBDIR)*.c $(LIBDIR)*.h

delete:
	rm $(LIBF)

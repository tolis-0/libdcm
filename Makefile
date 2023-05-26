CC = gcc
LFLAGS = -g -shared

SOURCEDIR = src/nstrings src/ntf
LIBDIR = /usr/local/lib/libdcm/
INCLUDEDIR = /usr/local/include/

SOURCEF = $(foreach D, $(SOURCEDIR), $(wildcard $(D)/*.c))
HEADERF = $(foreach D, $(SOURCEDIR), $(wildcard $(D)/*.h))
OBJECTF = $(patsubst %.c,%.o,$(SOURCEF))
LIBF = /usr/local/lib/libdcm.so

.PHONY: clean delete

all: compile link include

compile:
	cd src/nstrings && make
	cd src/ntf && make

link:
	$(CC) $(LFLAGS) -o libdcm.so $(OBJECTF) && \
	cp libdcm.so $(LIBF)

include:
	cp $(HEADERF) $(INCLUDEDIR)

clean:
	cd src/strings && make clean; \
	cd src/num_theory && make clean; \
	rm libdcm.so

delete:
	rm $(LIBF)

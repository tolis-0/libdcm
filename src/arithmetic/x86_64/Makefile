CC = gcc
ASMFLAGS = -g

SOURCEF = $(wildcard *.S)
OBJECTF = $(patsubst %.S,%.o,$(SOURCEF))

.PHONY: clean

all: $(OBJECTF)

$(OBJECTF):
	$(CC) $(ASMFLAGS) -c *.S

clean:
	rm -f *.o

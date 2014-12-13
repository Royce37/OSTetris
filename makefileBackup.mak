
CC=gcc
MKDIR=mkdir -p

CFLAGS=-Wall -fomit-frame-pointer -O3
LIBS=-lm -lncurses

SRCS=
OBJS=main.o Tetris.o View.o Tetrimino.o Stats.o
OUTPUT=Tetris


all:
	make build

build: $(OUTPUT)

$(OUTPUT): $(OBJS)
	$(CC) $(CFLAGS) -o $(OUTPUT) $(OBJS) $(LIBS)


depend: .depend

.depend: $(SRCS)
    rm -f ./.depend
    $(CXX) $(CPPFLAGS) -MM $^>>./.depend;

clean:
	$(RM) $(OBJS) $(OUTPUT)

dist-clean: clean
    $(RM) *~ .dependtool

include .depend





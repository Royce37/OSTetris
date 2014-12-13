CXX=g++
CC=gcc
MKDIR=mkdir -p

CFLAGS=-Wall -fomit-frame-pointer -O3
LIBS=-lm -lncurses

SRCS=main.cpp View.cpp Tetris.cpp Tetrimino.cpp Stats.cpp
OBJS=$(subst .cpp,.o,$(SRCS))
OUTPUT=Tetris

all:
	make build

build: $(OUTPUT)

$(OUTPUT): $(OBJS)
	$(CXX) $(CFLAGS) -o $(OUTPUT) $(OBJS) $(LIBS)


depend: .depend

.depend: $(SRCS)
	rm -f ./.depend
	$(CXX) $(CPPFLAGS) -MM $^>>./.depend;

clean:
	$(RM) $(OBJS) $(OUTPUT)

dist-clean: clean
	$(RM) *~ .dependtool

include .depend





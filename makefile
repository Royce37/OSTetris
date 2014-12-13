
MANDIR=$(DESTDIR)/usr/share/man/man6/
BINDIR=$(DESTDIR)/usr/games/

CC=gcc
MKDIR=mkdir -p
#INSTALL=install

CFLAGS=-Wall -fomit-frame-pointer -O3
LIBS=-lm -lncurses

OBJS=main.o Tetris.o View.o Tetrimino.o Stats.o
OUTPUT=Tetris
#MANS=ctris.6.gz


all:
	make build
	
#config:	
#	./create_config.sh

build: $(OUTPUT)

$(OUTPUT): $(OBJS)
	$(CC) $(CFLAGS) -o $(OUTPUT) $(OBJS) $(LIBS)


%.o: %.cpp
	$(CC) $(CFLAGS) -c $<


clean:
	$(RM) $(OBJS) $(OUTPUT) config.h





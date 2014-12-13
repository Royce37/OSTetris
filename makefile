
MANDIR=$(DESTDIR)/usr/share/man/man6/
BINDIR=$(DESTDIR)/usr/games/

CC=gcc
MKDIR=mkdir -p
#INSTALL=install

CFLAGS=-Wall -fomit-frame-pointer -O3
LIBS=-lm -lncurses

OBJS=Main.o Tetris.o View.o Tetrimino.o Stats.o
OUTPUT=Tetris
#MANS=ctris.6.gz


all:
	make config
	make build
	
config:	
	./create_config.sh

build: $(OUTPUT)

$(OUTPUT): $(OBJS)
	$(CC) $(CFLAGS) -o $(OUTPUT) $(OBJS) $(LIBS)


%.o: %.c
	$(CC) $(CFLAGS) -c $<


clean:
	$(RM) $(OBJS) $(OUTPUT) config.h


#install:
#	$(MKDIR) $(BINDIR) $(MANDIR)
#	$(INSTALL) $(OUTPUT) $(BINDIR)
#	$(INSTALL) -m 644 $(MANS) $(MANDIR)




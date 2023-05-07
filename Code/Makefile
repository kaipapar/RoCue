CC = gcc
CFLAGS = -Wall -Wextra -std=c18 -lncurses -lmenu -lm
SOURCES = *.c

all: Rogue #run clean

Rogue: 
		$(CC) $(SOURCES) $(CFLAGS) -o Rogue

run:
		./Rogue

clean:
		rm Rogue
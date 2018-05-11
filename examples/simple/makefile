#
# Copyright (c) 2018 Maciej Gorzkowski
#
# This file is licensed under the MIT License.
# Full license text is available in 'LICENSE'.
#

CC = gcc
INCLUDE_DIR = ../../include

all: prog.elf

run: prog.elf
	./prog.elf

clean:
	rm -f *.o
	rm -f prog.elf

prog.elf: real.o prog.o
	$(CC) -o prog.elf $? -lm
	rm $?

real.o: ../../src/real.c
	$(CC) -c -o $@ $?

prog.o: prog.c
	$(CC) -c -o $@ $? -I$(INCLUDE_DIR)

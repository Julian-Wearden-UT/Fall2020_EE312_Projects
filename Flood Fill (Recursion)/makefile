# target: dependencies
# <tab> rule

# make (without arguments) executes first rule in file
# Ideally, one target for every object file and a target for final binary. 

C_FLAGS = --std=c99 -O0 -g -Wall -Werror

C_FILES=$(wildcard *.c)
C_O_FILES=$(subst .c,.o,$(C_FILES))

O_FILES = $(C_O_FILES)
DEFAULT = ./flood_fill fake_picture.txt


flood_fill: $(O_FILES)
	gcc -o flood_fill $(O_FILES)

$(C_O_FILES) : %.o : %.c
	gcc $(C_FLAGS) -MD -o $*.o -c $*.c

clean:
	rm -rf *.o flood_fill

debug:
	make
	gdb flood_fill

test:
	make
	$(DEFAULT)

memory:
	make
	valgrind $(DEFAULT)
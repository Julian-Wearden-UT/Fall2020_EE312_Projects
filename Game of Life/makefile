# target: dependencies
# <tab> rule

# make (without arguments) executes first rule in file
# Ideally, one target for every object file and a target for final binary. 

life: life.o life_driver.o
	c99 -o life life.o life_driver.o

life.o: life.c
	c99 -g -c life.c

life_driver.o: life_driver.c
	c99 -g -c life_driver.c

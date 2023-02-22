# name of the program
NAME = plagiarismCatcher

# warning flags
# uncomment for extra safety
WARNINGS = -Wall -Werror # -Wextra -Wpedantic

# language standards
CPP_STD = --std=c++11
C_STD = --std=c11

# choose from debug or fast configuration
DEBUG = -O0 -g
FAST = -O3

# change to $(FAST) to enable compiler optimizations
OPTIMIZATION = $(FAST)

# compiler flags
CPP_FLAGS = $(CPP_STD) $(OPTIMIZATION) $(WARNINGS)
C_FLAGS = $(C_STD) $(OPTIMIZATION) $(WARNINGS)

# cpp files
CPP_FILES=$(wildcard *.cpp)
CPP_O_FILES=$(subst .cpp,.o,$(CPP_FILES))

# cc files
CC_FILES=$(wildcard *.cc)
CC_O_FILES=$(subst .cc,.o,$(CC_FILES))

# c files
C_FILES=$(wildcard *.c)
C_O_FILES=$(subst .c,.o,$(C_FILES))

# get complete list of object files
O_FILES = $(CPP_O_FILES) $(CC_O_FILES) $(C_O_FILES)

# uncomment and change value to change command line args
# ARGS = sample.txt

# uncomment to execute program with command line args
EXECUTE = ./$(NAME) # $(ARGS)

# uncomment to debug with command line args
GDB = gdb ./$(NAME) # --args $(ARGS)

$(NAME) : $(O_FILES)
	g++ $(CPP_STD) -o $(NAME) $(O_FILES)

$(CPP_O_FILES) : %.o : %.cpp
	g++ $(CPP_FLAGS) -MD -o $*.o -c $*.cpp

$(CC_O_FILES) : %.o : %.cc
	g++ $(CPP_FLAGS) -MD -o $*.o -c $*.cc

$(C_O_FILES) : %.o : %.c
	gcc $(C_FLAGS) -MD -o $*.o -c $*.c

# make run to compile and execute
run: $(NAME)
	$(EXECUTE)

# make debug to compile and start gdb
debug: $(NAME)
	$(GDB)

clean:
	rm -rf *.o $(NAME)
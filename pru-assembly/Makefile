pru = prucode
project = main

LIB_PATH = .
LIBRARIES = pthread prussdrv
INCLUDES = -I. ${LIB_PATH}

SOURCES =  main.cpp

EXTRA_DEFINE =
CC = g++
CFLAGS = $(EXTRA_DEFINE)
PASM = pasm

all : $(pru) $(project)
pru : $(pru)
project: $(project)

$(project) : $(project:%=%.cpp)
	$(CC) $(CFLAGS) -c -o $@.o $@.cpp
	$(CC) $@.o $(LIB_PATH:%=-L%) $(LIBRARIES:%=-l%) -o $@

clean :
	rm -rf *.o *.bin $(project) core *~

$(pru) : $(pru:%=%.p)
	$(PASM) -b $@.p

# Add additional project sources like this:
# SRCS += X.c
#
# all the files will be generated with this name (main.o, etc)

#Name of Project
PROJ=main

#Extra Sources to be added
SOURCES = $(PROJ).c

#Extra Include directories
INCLUDE= -I.h

#Libraries to be added
LIBS= -lpthread -lm

#Compiler Option flags
CFLAGS=-Wall
CC=gcc

OBJECTS= $(SOURCES:main.c=main.o)


$(PROJ): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS) $(INCLUDE)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(LIBS) $(INCLUDE)

clean:
	$(RM) $(PROJ)
	$(RM) *.o

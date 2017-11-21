# Add additional project sources like this:
# SRCS += X.c
#
# all the files will be generated with this name (main.o, etc)

# Disable built-in rules.
# If this is not done, the rule for % will not be used
.SUFFIXES:

# Don't delete .o files
.PRECIOUS: %.o

#Name of Project
PROJ=h5_write h5_read

#Extra Include directories
INCLUDE= -I.

#Libraries to be added
LIBS=

#Compiler Option flags
CFLAGS=-Wall -g
CC=h5cc

all: $(PROJ)

%: %.o shared.o
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS) $(INCLUDE)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(LIBS) $(INCLUDE)

clean:
	$(RM) *.h5
	$(RM) $(PROJ)
	$(RM) *.o

PP=gcc
COMPFLAGS= -Wall -pedantic -O2

###################################################################################

NEWSH_OBJ= newsh.o
EP1_OBJ= ep1.o

###################################################################################


all: newsh ep1 

newsh.o: newsh.h
ep1.o: ep1.h

newsh: ${NEWSH_OBJ}
	${PP} ${COMPFLAGS} -o newsh newsh.c -lreadline
	@rm -rf *.o

ep1: ${EP1_OBJ}
	${PP} ${COMPFLAGS} -o ep1 ep1.c -lpthread 
	@rm -rf *.o
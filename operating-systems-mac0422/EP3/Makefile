PP=gcc
COMPFLAGS= -Wall -pedantic -O2

###################################################################################

EP3_OBJ= ep3.o

###################################################################################


all: ep3

ep3.o: ep3.h

ep3: ${EP3_OBJ}
	${PP} ${COMPFLAGS} -o ep3 -O ep3.c -lpthread -lreadline
	@rm -rf *.o%
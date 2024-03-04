PP=gcc
COMPFLAGS= -Wall -ansi -O2 -g
#OTHERS= regexp.cpp

###################################################################################

OBJS= newsh.o

###################################################################################

newsh: ${OBJS}
	${PP} ${COMPFLAGS} -o newsh newsh.c -lreadline
	@rm -rf *.o


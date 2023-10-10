BIN:=bin
CODEDIRS:= ./src

CC:=cc
OPT:=-O0
DEPFLAGS:=-MD -MP
CFLAGS:=-Wextra -Wall -g ${DEPFLAGS} 

CFILES!= find ${CODEDIRS} -name "*.c"
HFILES!= find ${CODEDIRS} -name "*.h"
OFILES:= ${CFILES:S/.c/.o/g}
DFILES:= ${CFILES:S/.c/.d/g}
GCHFILES:= ${HFILES:S/.h/.h.gch/g}

.SUFFIXES: .o .c

.PHONY: all clean

all: ${BIN}

.c.o:
	${CC} ${CFLAGS} -c $< -o $@

${BIN}: ${OFILES}
	${CC} ${OFILES} -o $@  

clean:
	@rm -rf ${OFILES} ${DFILES} ${GCHFILES}


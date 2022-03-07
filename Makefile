SRC = src/fetch.c
CC ?= cc
CFLAGS = -O2 -std=c99 -Wall -Wextra
DEBUGFLAGS = -g -Og -std=c99 -Wall -Wextra
PREFIX ?= /usr/local

all: afetch

afetch: ${SRC} src/config.h src/color.h
	${CC} ${CFLAGS} ${SRC} -o afetch

debug:
	${CC}  ${DEBUGFLAGS} ${SRC} -o afetch-debug

clean:
	rm -rf afetch afetch.dSYM afetch-debug afetch-debug.dSYM

install: afetch
	mkdir -p ${DESTDIR}${PREFIX}/bin
	cp afetch ${DESTDIR}${PREFIX}/bin
	chmod 711 ${DESTDIR}${PREFIX}/bin/afetch

uninstall:
	rm -f ${DESTDIR}${PREFIX}/bin/afetch

.PHONY: all clean debug install uninstall

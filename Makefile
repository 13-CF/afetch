SRC = src/fetch.c
CC ?= cc
CFLAGS = -O2 -std=c99 -Wall -Wextra
LDFLAGS = -lpthread
DEBUGFLAGS = -g
PREFIX ?= /usr/local

all: afetch

afetch: ${SRC} src/config.h src/colour.h
	${CC} ${CFLAGS} ${SRC} ${LDFLAGS} -o afetch

debug:
	${CC} ${CFLAGS} ${DEBUGFLAGS} ${SRC} ${LDFLAGS} -o afetch-debug

clean:
	rm -rf afetch afetch.dSYM

install:
	mkdir -p ${DESTDIR}${PREFIX}/bin
	cp afetch ${DESTDIR}${PREFIX}/bin
	chmod 711 ${DESTDIR}${PREFIX}/bin/afetch

uninstall:
	rm -f ${DESTDIR}${PREFIX}/bin/afetch

.PHONY: all clean debug install uninstall

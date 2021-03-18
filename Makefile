SRC = src/fetch.c
CC = cc
CFLAGS = -O2 -std=c99 -Wall -Wextra
PREFIX ?= /usr/local
MANPREFIX ?= ${PREFIX}/share/man

all: afetch

afetch: ${SRC} src/config.h
	${CC} ${CFLAGS} ${SRC} -o afetch

clean:
	rm -f afetch

install:
	mkdir -p ${DESTDIR}${PREFIX}/bin
	chmod 711 ./afetch
	cp ./afetch ${DESTDIR}${PREFIX}/bin
	mkdir -p ${DESTDIR}${MANPREFIX}/man1
	chmod 644 ./src/afetch.1
	cp src/afetch.1 ${DESTDIR}${MANPREFIX}/man1
uninstall:
	rm -f ${DESTDIR}${PREFIX}/bin/afetch ${DESTDIR}${MANPREFIX}/man1/afetch.1

.PHONY: clean all install


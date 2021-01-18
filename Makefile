SRC = src/fetch.c
CC = cc
CFLAGS = -O2 -std=c99 -Wall -Wextra
PREFIX ?= /usr/local

all: afetch

afetch: $(SRC) src/config.h
	$(CC) $(CFLAGS) $(SRC) -o afetch

clean:
	rm -f afetch

install:
	install -o root -g root -d ${DESTDIR}${PREFIX}/bin
	install -o root -g root -d ${DESTDIR}${PREFIX}/share/man/man1
	install -o root -g root -m 711 ./afetch ${DESTDIR}${PREFIX}/bin/afetch
	install -o root -g root -m 644 ./src/afetch.1 ${DESTDIR}${PREFIX}/share/man/man1/afetch.1

uninstall:
	rm -f ${DESTDIR}${PREFIX}/bin/afetch ${DESTDIR}${PREFIX}/man/man1/afetch.1

.PHONY: clean all install


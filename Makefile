SRC = fetch.c
CC = cc
CFLAGS = -O2
PREFIX ?= /usr/local

all: afetch

afetch:
	$(CC) $(CFLAGS) $(SRC) -o afetch $(LDFLAGS)
clean:
	rm afetch
install:
	mkdir -p ${DESTDIR}${PREFIX}/bin
	mkdir -p ${DESTDIR}${PREFIX}/share/man/man1
	cp ./afetch ${DESTDIR}${PREFIX}/bin/afetch
	chmod 711 ${DESTDIR}${PREFIX}/bin/afetch
	cp ./afetch.1 ${DESTDIR}${PREFIX}/share/man/man1/afetch.1
uninstall:
	rm -f ${DESTDIR}${PREFIX}/bin/afetch ${DESTDIR}${PREFIX}/man/man1/afetch.1
.PHONY: clean all install

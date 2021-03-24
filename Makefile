SRC = src/fetch.c
CC = cc
CFLAGS = -O2 -std=c99 -Wall -Wextra
LDFLAGS = -lpthread
DEBUGFLAGS = -g
PREFIX ?= /usr/local

all: afetch

afetch: 
	${CC} ${CFLAGS} ${SRC} ${LDFLAGS} -o afetch
debug:
	${CC} ${CFLAGS} ${DEBUGFLAGS} ${SRC} ${LDFLAGS} -o afetch-debug
clean:
	rm -rf afetch afetch.dSYM
install:
	chmod 711 ./afetch
	cp ./afetch ${DESTDIR}${PREFIX}/bin
uninstall:
	rm -f ${DESTDIR}${PREFIX}/bin/afetch 
.PHONY: clean all install


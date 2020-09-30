SRC = fetch.c
CC = gcc
CFLAGS = -O2

all: afetch

afetch:
	$(CC) $(CFLAGS) $(SRC) -o afetch
clean:
	rm afetch
install:
	cp ./afetch /usr/local/bin/afetch
	chmod 711 /usr/local/bin/afetch
uninstall:
	rm -f /usr/local/bin/afetch
.PHONY: clean all install

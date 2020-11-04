SRC = fetch.c
CC = cc
CFLAGS = -O2

all: afetch

afetch:
	$(CC) $(CFLAGS) $(SRC) -o afetch $(LDFLAGS)
clean:
	rm afetch
install:
	cp ./afetch /usr/local/bin/afetch
	chmod 711 /usr/local/bin/afetch
	cp ./afetch.1 /usr/local/share/man/man1/afetch.1
uninstall:
	rm -f /usr/local/bin/afetch /usr/local/man/man1/afetch.1
.PHONY: clean all install

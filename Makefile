SRC = fetch.c
CC = gcc

all: afetch

afetch:
	$(CC) $(SRC) -o afetch
clean:
	rm aftech
install:
	cp ./afetch /usr/bin/afetch
	chmod 711 /usr/bin/afetch

.PHONY: clean all install

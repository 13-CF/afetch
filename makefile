.POSIX:

SRC        = src/fetch
BIN        = afetch
CFLAGS     = -O2 -Wall -Wextra
LDFLAGS    = -lpthread
DEBUGFLAGS = -g -Og -Wall -Wextra
PREFIX     = /usr/local
BINDIR     = $(DESTDIR)$(PREFIX)/bin

$(BIN): $(SRC)
	mv $< $@

$(SRC):

debug:
	$(CC) $(DEBUGFLAGS) $(LDFLAGS) $(SRC).c -o $(BIN)-$@

clean:
	rm -f $(BIN) $(BIN)-debug

install:
	mkdir -p $(BINDIR)
	cp $(BIN) $(BINDIR)
	chmod 711 $(BINDIR)/$(BIN)

uninstall:
	rm -f $(BINDIR)/$(BIN)

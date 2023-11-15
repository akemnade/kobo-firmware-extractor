CC=gcc
CFLAGS=-Wall -Wextra

all: extract-kobohidden

install:
	install -dm755 "$(DESTDIR)"/"$(PREFIX)"/bin
	install -Dm755 extract-kobohidden "$(DESTDIR)"/"$(PREFIX)"/bin/extract-kobohidden
	install -Dm755 extract-waveform.sh "$(DESTDIR)"/"$(PREFIX)"/bin/extract-waveform.sh

clean:
	rm extract-kobohidden

.PHONY: all clean

CC=gcc

all: extract-kobohidden

install:
	install -dm755 "$(DESTDIR)"/bin
	install -Dm755 extract-kobohidden "$(DESTDIR)"/bin/extract-kobohidden
	install -Dm755 extract-waveform.sh "$(DESTDIR)"/bin/extract-waveform.sh

clean:
	rm extract-kobohidden

.PHONY: all clean

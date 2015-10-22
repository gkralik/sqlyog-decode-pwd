CC=gcc
BIN=sqlyog-decode-pwd

sqlyog-decode-pwd: decode.c
	$(CC) -o $(BIN) decode.c

clean:
	rm -f $(BIN)
	rm -f *.o

.phony: clean

CC = clang
CFLAGS = -std=c23 -Wall -Wextra -g
LDFLAGS = -lSDL2 -lm

renderer: src/*.c
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f renderer

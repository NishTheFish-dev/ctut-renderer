CC = clang
CFLAGS = -std=c23 -Wall -Wextra -g

ifeq ($(OS),Windows_NT)
	TARGET = renderer.exe
	LDFLAGS = -lSDL2main -lSDL2 -lm
	RM = del /Q
else
	TARGET = renderer
	LDFLAGS = -lSDL2 -lm
	RM = rm -f
endif

all: $(TARGET)

$(TARGET): src/*.c
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	$(RM) $(TARGET)
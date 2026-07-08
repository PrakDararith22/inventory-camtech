CC ?= gcc
CFLAGS ?= -Wall -Wextra
SRC = src/main.c src/fileio.c src/utils.c src/features.c
OBJ = $(SRC:.c=.o)

ifeq ($(OS),Windows_NT)
    EXE = inventory.exe
    OBJ_PATTERN = src\\*.o
    RM = del /Q
else
    EXE = inventory
    OBJ_PATTERN = src/*.o
    RM = rm -f
endif

all: $(EXE)

$(EXE): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: all clean run

run: $(EXE)
	./$(EXE)

clean:
	$(RM) $(OBJ_PATTERN) $(EXE) inventory.dat transactions.log

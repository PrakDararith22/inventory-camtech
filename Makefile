CC = gcc
CFLAGS = -Wall -Wextra
SRC = src/main.c src/fileio.c src/utils.c src/add_product.c src/stock.c src/search.c src/reports.c src/audit.c
OBJ = $(SRC:.c=.o)

inventory: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean run

run: inventory
	./inventory

clean:
	rm -f src/*.o inventory inventory.dat transactions.log

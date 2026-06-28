#ifndef INVENTORY_H
#define INVENTORY_H

#define MAX_PRODUCTS 100
#define NAME_LEN 50
#define CODE_LEN 10
#define CODE_PREFIX "PRD"

typedef struct {
    char code[CODE_LEN];
    char name[NAME_LEN];
    int quantity;
    float price;
    int minStock;
} Product;

#endif

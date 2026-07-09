#include <stdio.h>
#include <string.h>
#include "add_product.h"
#include "fileio.h"
#include "utils.h"
#include "inventory.h"

void addProduct() {
    printf("\n--- Add Product ---\n");

    char code[CODE_LEN];
    generateCode(code);
    printf("Generated code: %s\n", code);

    Product p;
    strcpy(p.code, code);

    while (1) {
        readString("Enter product name: ", p.name, NAME_LEN);
        if (p.name[0] != '\0') break;
        printf("Name cannot be empty.\n");
    }

    while (1) {
        p.quantity = getIntInput("Enter quantity: ");
        if (p.quantity >= 0) break;
        printf("Quantity cannot be negative.\n");
    }

    while (1) {
        p.price = getFloatInput("Enter price: ");
        if (p.price > 0) break;
        printf("Price must be positive.\n");
    }

    while (1) {
        p.minStock = getIntInput("Enter minimum stock level: ");
        if (p.minStock >= 0) break;
        printf("Minimum stock cannot be negative.\n");
    }

    if (insertProduct(&p)) {
        appendLog("PRODUCT_ADD", p.code, p.quantity);
        printf("Product added successfully!\n");
    } else {
        printf("Failed to add product.\n");
    }
}


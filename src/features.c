#include <stdio.h>
#include <string.h>
#include "features.h"
#include "fileio.h"
#include "utils.h"

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

void searchProduct() {
    printf("\n--- Search Product ---\n");

    printf("1. Search by Code\n");
    printf("2. Search by Name\n");
    int choice;
    while (1) {
        choice = getIntInput("Enter choice (1-2): ");
        if (choice == 1 || choice == 2) break;
        printf("Invalid choice.\n");
    }

    if (choice == 1) {
        char code[CODE_LEN];
        readString("Enter product code: ", code, CODE_LEN);

        Product p;
        if (getProduct(code, &p)) {
            printf("\n%-10s %-20s %8s %8s\n", "Code", "Name", "Qty", "Price");
            printf("--------------------------------------------------------\n");
            printf("%-10s %-20s %8d %8.2f\n", p.code, p.name, p.quantity, p.price);
        } else {
            printf("Product not found.\n");
        }
    } else {
        char searchTerm[NAME_LEN];
        readString("Enter product name (or part): ", searchTerm, NAME_LEN);

        char searchLower[NAME_LEN];
        toLowerCase(searchTerm, searchLower);

        Product products[MAX_PRODUCTS];
        int count = getAllProducts(products, MAX_PRODUCTS);

        int found = 0;
        for (int i = 0; i < count; i++) {
            char nameLower[NAME_LEN];
            toLowerCase(products[i].name, nameLower);
            if (strstr(nameLower, searchLower) != NULL) {
                if (!found) {
                    printf("\n%-10s %-20s %8s %8s\n", "Code", "Name", "Qty", "Price");
                    printf("--------------------------------------------------------\n");
                }
                printf("%-10s %-20s %8d %8.2f\n",
                       products[i].code, products[i].name,
                       products[i].quantity, products[i].price);
                found = 1;
            }
        }

        if (!found) {
            printf("No matching products found.\n");
        }
    }
}

void stockIn() {
    printf("\n--- Stock In ---\n");

    char code[CODE_LEN];
    readString("Enter product code: ", code, CODE_LEN);

    Product p;
    if (!getProduct(code, &p)) {
        printf("Product not found.\n");
        return;
    }

    printf("Current quantity: %d\n", p.quantity);

    int qty;
    while (1) {
        qty = getIntInput("Enter quantity to add: ");
        if (qty > 0) break;
        printf("Quantity must be positive.\n");
    }

    p.quantity += qty;
    updateProductQty(p.code, p.quantity);
    appendLog("STOCK_IN", p.code, qty);
    printf("Stock in successful! New quantity: %d\n", p.quantity);
}

void stockOut() {
    printf("\n--- Stock Out ---\n");

    char code[CODE_LEN];
    readString("Enter product code: ", code, CODE_LEN);

    Product p;
    if (!getProduct(code, &p)) {
        printf("Product not found.\n");
        return;
    }

    printf("Current quantity: %d\n", p.quantity);

    int qty;
    while (1) {
        qty = getIntInput("Enter quantity to remove: ");
        if (qty <= 0) {
            printf("Quantity must be positive.\n");
        } else if (qty > p.quantity) {
            printf("Insufficient stock. Available: %d\n", p.quantity);
        } else {
            break;
        }
    }

    p.quantity -= qty;
    updateProductQty(p.code, p.quantity);
    appendLog("STOCK_OUT", p.code, qty);
    printf("Stock out successful! Remaining: %d\n", p.quantity);
}

void lowStockReport() {
    printf("\n--- Low Stock Report ---\n");

    Product products[MAX_PRODUCTS];
    int count = getAllProducts(products, MAX_PRODUCTS);

    if (count == 0) {
        printf("No products in inventory.\n");
        return;
    }

    int found = 0;
    for (int i = 0; i < count; i++) {
        if (products[i].quantity < products[i].minStock) {
            if (!found) {
                printf("\n%-10s %-20s %8s %8s %s\n", "Code", "Name", "Qty", "Min", "Status");
                printf("--------------------------------------------------------\n");
            }
            printf("%-10s %-20s %8d %8d %s\n",
                   products[i].code, products[i].name,
                   products[i].quantity, products[i].minStock, "LOW STOCK");
            found = 1;
        }
    }

    if (!found) {
        printf("All products are adequately stocked.\n");
    }
}

void inventoryValue() {
    printf("\n--- Inventory Value Report ---\n");

    Product products[MAX_PRODUCTS];
    int count = getAllProducts(products, MAX_PRODUCTS);

    if (count == 0) {
        printf("No products in inventory.\n");
        return;
    }

    printf("\n%-10s %-20s %8s %12s %8s\n", "Code", "Name", "Qty", "Unit Price", "Total");
    printf("--------------------------------------------------------\n");

    float grandTotal = 0;
    for (int i = 0; i < count; i++) {
        float total = products[i].quantity * products[i].price;
        grandTotal += total;
        printf("%-10s %-20s %8d %12.2f %8.2f\n",
               products[i].code, products[i].name,
               products[i].quantity, products[i].price, total);
    }

    printf("--------------------------------------------------------\n");
    printf("GRAND TOTAL: %.2f\n", grandTotal);

    int hasWarnings = 0;
    for (int i = 0; i < count; i++) {
        if (products[i].quantity < products[i].minStock) {
            if (!hasWarnings) {
                printf("\n--- Low Stock Warnings ---\n");
                hasWarnings = 1;
            }
            printf("  %s (%s): %d remaining (min: %d)\n",
                   products[i].code, products[i].name,
                   products[i].quantity, products[i].minStock);
        }
    }
}

void viewAuditLog() {
    printf("\n--- Audit Log ---\n");
    viewLog();
}

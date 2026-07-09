#include <stdio.h>
#include <string.h>
#include "search.h"
#include "fileio.h"
#include "utils.h"
#include "inventory.h"

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
#include <stdio.h>
#include "add_product.h"
#include "stock.h"

void displayMenu();

int main() {
    int choice;
    do {
        displayMenu();
        scanf("%d", &choice);
        while (getchar() != '\n');
        switch (choice) {
        case 1: addProduct(); break;
        case 2: stockIn(); break;
        case 3: stockOut(); break;
        case 4: printf("Exiting... Goodbye!\n"); break;
        default: printf("Invalid choice. Enter 1-4.\n");
        }
    } while (choice != 4);
    return 0;
}

void displayMenu() {
    printf("\n====================================\n");
    printf("  INVENTORY MANAGEMENT SYSTEM\n");
    printf("         - CAMTECH -\n");
    printf("====================================\n");
    printf("1. Add Product\n");
    printf("2. Stock In\n");
    printf("3. Stock Out\n");
    printf("4. Exit\n");
    printf("------------------------------------\n");
    printf("Enter your choice: ");
}

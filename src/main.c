#include <stdio.h>
#include "add_product.h"

void displayMenu();

int main() {
    int choice;
    do {
        displayMenu();
        scanf("%d", &choice);
        while (getchar() != '\n');
        switch (choice) {
        case 1: addProduct(); break;
        case 2: printf("Exiting... Goodbye!\n"); break;
        default: printf("Invalid choice. Enter 1-2.\n");
        }
    } while (choice != 2);
    return 0;
}

void displayMenu() {
    printf("\n====================================\n");
    printf("  INVENTORY MANAGEMENT SYSTEM\n");
    printf("         - CAMTECH -\n");
    printf("====================================\n");
    printf("1. Add Product\n");
    printf("2. Exit\n");
    printf("------------------------------------\n");
    printf("Enter your choice: ");
}

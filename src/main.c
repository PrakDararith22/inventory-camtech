#include <stdio.h>
#include "features.h"
#include "utils.h"

void displayMenu() {
    printf("\n====================================\n");
    printf("  INVENTORY MANAGEMENT SYSTEM\n");
    printf("         - CAMTECH -\n");
    printf("====================================\n");
    printf("1. Add Product\n");
    printf("2. Stock In\n");
    printf("3. Stock Out\n");
    printf("4. Search Product\n");
    printf("5. Low Stock Report\n");
    printf("6. Inventory Value\n");
    printf("7. View Audit Log\n");
    printf("8. Exit\n");
    printf("------------------------------------\n");
}

int main() {
    printf("====================================\n");
    printf("  INVENTORY MANAGEMENT SYSTEM\n");
    printf("         - CAMTECH -\n");
    printf("====================================\n");
    printf("  Group Members:\n");
    printf("  1. Person 1 - File DB SDK\n");
    printf("  2. Person 2 - Add & Search\n");
    printf("  3. Person 3 - Stock In & Out\n");
    printf("  4. Person 4 - Reports & Audit\n");
    printf("  5. Person 5 - Main Menu & Utils\n");
    printf("====================================\n");

    int choice;
    do {
        displayMenu();
        choice = getIntInput("Enter your choice: ");

        if (choice < 1 || choice > 8) {
            printf("Invalid choice. Enter 1-8.\n");
            continue;
        }

        switch (choice) {
        case 1:
            addProduct();
            break;
        case 2:
            stockIn();
            break;
        case 3:
            stockOut();
            break;
        case 4:
            searchProduct();
            break;
        case 5:
            lowStockReport();
            break;
        case 6:
            inventoryValue();
            break;
        case 7:
            viewAuditLog();
            break;
        case 8:
            printf("Exiting... Goodbye!\n");
            break;
        }
    } while (choice != 8);

    return 0;
}

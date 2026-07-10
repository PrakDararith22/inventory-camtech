/**
 * @file    main.c
 * @author  Prak Dararith
 * @author  Thina
 * @author  Kelly
 * @author  Lida
 * @author  Lado Ponn
 * @author  Samrith
 * @version v1.0
 * @date    9-July-2026
 * @brief   Inventory Management System.
 *
 * This program is a console-based inventory management system developed
 * using the C programming language. It allows staff to manage product
 * inventory efficiently by providing the following features:
 *
 * - Add new products.
 * - Stock in and stock out products.
 * - Search products by code or name.
 * - Generate low stock and inventory value reports.
 * - View audit log for all transactions.
 *
 * The system uses a binary file (inventory.dat) for persistent storage
 * and a transaction log (transactions.log) for auditing purposes.
 *
 * @attention
 * This project was developed as part of the Computer Fundamental course
 * at CamTech University.
 */

#include <stdio.h>
#include "add_product.h"
#include "stock.h"
#include "search.h"
#include "report.h"
#include "audit.h"

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
        case 4: searchProduct(); break;
        case 5: lowStockReport(); break;
        case 6: inventoryValue(); break;
        case 7: viewAuditLog(); break;
        case 8: printf("Exiting... Goodbye!\n"); break;
        default: printf("Invalid choice. Enter 1-8.\n");
        }
    } while (choice != 8);
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
    printf("4. Search Product\n");
    printf("5. Low Stock Report\n");
    printf("6. Inventory Value\n");
    printf("7. View Audit Log\n");
    printf("8. Exit\n");
    printf("------------------------------------\n");
    printf("Enter your choice: ");
}

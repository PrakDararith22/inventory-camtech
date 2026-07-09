#include <stdio.h>
#include "reports.h"
#include "fileio.h"
#include "inventory.h"

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


/**
 * @file    stock.c
 * @author  samrith
 * @version v1.0
 * @date    9-July-2026
 * @brief   Stock in and stock out operations.
 *
 * Implements adding stock to (stock in) and removing stock from
 * (stock out) existing products, updating the stored quantities and
 * recording each movement in the transaction log.
 *
 * @attention
 * This project was developed as part of the Computer Fundamental course
 * at CamTech University.
 */

#include <stdio.h>
#include "stock.h"
#include "fileio.h"
#include "utils.h"
#include "inventory.h"

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

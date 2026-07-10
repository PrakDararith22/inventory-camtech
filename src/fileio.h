/**
 * @file    fileio.h
 * @author  Lida
 * @author  thina
 * @version v1.0
 * @date    9-July-2026
 * @brief   Header for inventory file I/O operations.
 *
 * @attention
 * This project was developed as part of the Computer Fundamental course
 * at CamTech University.
 */

#ifndef FILEIO_H
#define FILEIO_H

#include "inventory.h"

int insertProduct(Product *p);
int productNameExists(const char *name);
int getProduct(const char *code, Product *out);
int getAllProducts(Product *out, int max);
int updateProductQty(const char *code, int newQty);
int getProductCount();
void generateCode(char *outCode);
void appendLog(const char *action, const char *code, int qty);

#endif
#ifndef FILEIO_H
#define FILEIO_H

#include "inventory.h"

int insertProduct(Product *p);
int getProduct(const char *code, Product *out);
int getAllProducts(Product *out, int max);
int updateProductQty(const char *code, int newQty);
int getProductCount();
void generateCode(char *outCode);
void appendLog(const char *action, const char *code, int qty);

#endif
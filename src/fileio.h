#ifndef FILEIO_H
#define FILEIO_H

#include "inventory.h"

int insertProduct(Product *p);
int getProduct(const char *code, Product *out);
int updateProductQty(const char *code, int newQty);
int getProductCount();
int getAllProducts(Product *out, int max);
void generateCode(char *outCode);
void appendLog(const char *action, const char *code, int qty);
void viewLog();

#endif

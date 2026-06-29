#ifndef FILEIO_H
#define FILEIO_H

#include "inventory.h"

int insertProduct(Product *p);
int getProduct(const char *code, Product *out);

#endif

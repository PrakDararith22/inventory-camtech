#ifndef FILEIO_H
#define FILEIO_H

#include "inventory.h"

int insertProduct(Product *p);
void generateCode(char *outCode);
void appendLog(const char *action, const char *code, int qty);

#endif
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "fileio.h"

int insertProduct(Product *p) {
    FILE *fp = fopen("inventory.dat", "ab");
    if (fp == NULL) return 0;

    int written = fwrite(p, sizeof(Product), 1, fp);
    fclose(fp);
    return written == 1;
}

int getProduct(const char *code, Product *out) {
    FILE *fp = fopen("inventory.dat", "rb");
    if (fp == NULL) return 0;

    Product p;
    while (fread(&p, sizeof(Product), 1, fp) == 1) {
        if (strcmp(p.code, code) == 0) {
            *out = p;
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

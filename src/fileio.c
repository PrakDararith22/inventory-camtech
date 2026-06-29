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

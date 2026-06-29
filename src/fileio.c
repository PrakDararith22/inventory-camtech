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

int updateProductQty(const char *code, int newQty) {
    FILE *fp = fopen("inventory.dat", "rb+");
    if (fp == NULL) return 0;

    Product p;
    while (fread(&p, sizeof(Product), 1, fp) == 1) {
        if (strcmp(p.code, code) == 0) {
            p.quantity = newQty;
            fseek(fp, -sizeof(Product), SEEK_CUR);
            fwrite(&p, sizeof(Product), 1, fp);
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

int getProductCount() {
    FILE *fp = fopen("inventory.dat", "rb");
    if (fp == NULL) return 0;

    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    fclose(fp);
    return (int)(size / sizeof(Product));
}

int getAllProducts(Product *out, int max) {
    FILE *fp = fopen("inventory.dat", "rb");
    if (fp == NULL) return 0;

    int count = 0;
    while (count < max && fread(&out[count], sizeof(Product), 1, fp) == 1) {
        count++;
    }
    fclose(fp);
    return count;
}

void generateCode(char *outCode) {
    FILE *fp = fopen("inventory.dat", "rb");
    if (fp == NULL) {
        strcpy(outCode, "PRD001");
        return;
    }

    int maxNum = 0;
    Product p;
    while (fread(&p, sizeof(Product), 1, fp) == 1) {
        int num = atoi(p.code + 3);
        if (num > maxNum) maxNum = num;
    }
    fclose(fp);

    maxNum++;
    sprintf(outCode, "PRD%03d", maxNum);
}

void appendLog(const char *action, const char *code, int qty) {
    FILE *fp = fopen("transactions.log", "a");
    if (fp == NULL) return;

    time_t t = time(NULL);
    struct tm *tmInfo = localtime(&t);
    char timestamp[20];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", tmInfo);

    fprintf(fp, "[%s] %s code=%s qty=%d\n", timestamp, action, code, qty);
    fclose(fp);
}

void viewLog() {
    FILE *fp = fopen("transactions.log", "r");
    if (fp == NULL) {
        printf("No transactions recorded.\n");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), fp) != NULL) {
        printf("%s", line);
    }
    fclose(fp);
}

#include <stdio.h>
#include "fileio.h"

int insertProduct(Product *p)
{
    FILE *fp = fopen("inventory.dat", "ab");
    if (fp == NULL)
        return 0;

    int written = fwrite(p, sizeof(Product), 1, fp);
    fclose(fp);
    return written == 1;
}
int getProduct(const char *code, Product *out)
{
    FILE *fp = fopen("inventory.dat", "rb");
    if (fp == NULL)
        return 0;

    Product p;
    while (fread(&p, sizeof(Product), 1, fp) == 1)
    {
        if (strcmp(p.code, code) == 0)
        {
            *out = p;
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
}

int updateProductQty(const char *code, int newQty)
{
    FILE *fp = fopen("inventory.dat", "rb+");
    if (fp == NULL)
        return 0;

    Product p;
    while (fread(&p, sizeof(Product), 1, fp) == 1)
    {
        if (strcmp(p.code, code) == 0)
        {
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

int getProductCount()
{
    FILE *fp = fopen("inventory.dat", "rb");
    if (fp == NULL)
        return 0;

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
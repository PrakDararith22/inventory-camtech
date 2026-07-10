/**
 * @file    fileio.c
 * @author  Dararith
 * @author  Lida
 * @author  thina
 * @version v1.0
 * @date    10-July-2026
 * @brief   Persistent storage of inventory products.
 *
 * Implements reading and writing of products to the binary data file
 * (inventory.dat). Provides functions to insert, retrieve, update and
 * list products used by the rest of the application.
 *
 * @attention
 * This project was developed as part of the Computer Fundamental course
 * at CamTech University.
 */

#include "fileio.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int insertProduct(Product *p) {
  FILE *fp = fopen("inventory.dat", "ab");
  if (fp == NULL)
    return 0;

  int written = fwrite(p, sizeof(Product), 1, fp);
  fclose(fp);
  return written == 1;
}

int productNameExists(const char *name) {
  FILE *fp = fopen("inventory.dat", "rb");
  if (fp == NULL)
    return 0;

  char inputLower[NAME_LEN];
  toLowerCase(name, inputLower);

  Product p;
  while (fread(&p, sizeof(Product), 1, fp) == 1) {
    char storedLower[NAME_LEN];
    toLowerCase(p.name, storedLower);
    if (strcmp(storedLower, inputLower) == 0) {
      fclose(fp);
      return 1;
    }
  }
  fclose(fp);
  return 0;
}
int getProduct(const char *code, Product *out) {
  FILE *fp = fopen("inventory.dat", "rb");
  if (fp == NULL)
    return 0;

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
  if (fp == NULL)
    return 0;

  Product p;
  while (fread(&p, sizeof(Product), 1, fp) == 1) {
    if (strcmp(p.code, code) == 0) {
      p.quantity = newQty;
      // -sizeof(product) tell the fseek directl of -100
      // and seekcur is the c fla it is the starting line option
      // seek_set  : start line
      // seeK_cur : back line
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
  if (fp == NULL)
    return 0;

  fseek(fp, 0, SEEK_END);
  // It takes your file pointer (fp) and returns a regular number (a long
  // integer) representing the exact byte position of the cursor from the very
  // beginning of the file.
  //  it tell the amount of btyle all of hte data from the current cursor
  long size = ftell(fp);
  fclose(fp);
  return (int)(size / sizeof(Product));
}

int getAllProducts(Product *out, int max) {
  FILE *fp = fopen("inventory.dat", "rb");
  if (fp == NULL)
    return 0;

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
    // copy string from one place to toehr (source , disinate)
    strcpy(outCode, "PRD001");
    return;
  }

  int maxNum = 0;
  Product p;
  while (fread(&p, sizeof(Product), 1, fp) == 1) {
    // atoi stands for ASCII to Integer. It is a built-in function in C used to
    // convert a string of text characters (like "125") into an actual math
    // number (like 125).
    //
    // casting will giv ehte ascll value exmaple '5' ascll give sth 53 but aoit
    // give me '5' to 5
    // but if 'a' it will give 0 automatly
    int num = atoi(p.code + 3);
    if (num > maxNum)
      maxNum = num;
  }
  fclose(fp);

  maxNum++;
  sprintf(outCode, "PRD%03d", maxNum);
}

void appendLog(const char *action, const char *code, int qty) {
  FILE *fp = fopen("transactions.log", "a");
  if (fp == NULL)
    return;

  time_t t = time(NULL);
  struct tm *tmInfo = localtime(&t);
  char timestamp[20];
  strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", tmInfo);

  fprintf(fp, "[%s] %s code=%s qty=%d\n", timestamp, action, code, qty);
  fclose(fp);
}

#include <stdio.h>
#include "audit.h"

void viewAuditLog() {
    printf("\n--- Audit Log ---\n");

    FILE *fp = fopen("transactions.log", "r");
    if (fp == NULL) {
        printf("No audit log found.\n");
        return;
    }

    char line[256];
    int count = 0;
    while (fgets(line, sizeof(line), fp) != NULL) {
        printf("%s", line);
        count++;
    }
    fclose(fp);

    if (count == 0) {
        printf("Audit log is empty.\n");
    }
}

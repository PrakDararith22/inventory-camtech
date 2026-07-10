/**
 * @file    audit.c
 * @author  Lida
 * @version v1.0
 * @date    10-July-2026
 * @brief   View the transaction audit log.
 *
 * Reads and displays the transaction log (transactions.log) so staff can
 * review a chronological record of all inventory operations performed by
 * the system.
 *
 * @attention
 * This project was developed as part of the Computer Fundamental course
 * at CamTech University.
 */

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

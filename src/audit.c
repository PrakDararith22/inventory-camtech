#include <stdio.h>
#include "audit.h"
#include "fileio.h"

void viewAuditLog() {
    printf("\n--- Audit Log ---\n");
    viewLog();
}

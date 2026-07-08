#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "utils.h"

int getIntInput(const char *prompt) {
    char buffer[64];
    int value;
    while (1) {
        printf("%s", prompt);
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            if (feof(stdin)) exit(0);
            continue;
        }
        if (sscanf(buffer, "%d", &value) == 1) return value;
        printf("Invalid input.\n");
    }
}

float getFloatInput(const char *prompt) {
    char buffer[64];
    float value;
    while (1) {
        printf("%s", prompt);
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            if (feof(stdin)) exit(0);
            continue;
        }
        if (sscanf(buffer, "%f", &value) == 1) return value;
        printf("Invalid input.\n");
    }
}

void readString(const char *prompt, char *out, int maxLen) {
    printf("%s", prompt);
    if (fgets(out, maxLen, stdin) != NULL) {
        size_t len = strlen(out);
        if (len > 0 && out[len - 1] == '\n') {
            out[len - 1] = '\0';
        }
    } else if (feof(stdin)) {
        out[0] = '\0';
    }
}

void toLowerCase(const char *src, char *dst) {
    while (*src) {
        *dst = tolower((unsigned char)*src);
        src++;
        dst++;
    }
    *dst = '\0';
}

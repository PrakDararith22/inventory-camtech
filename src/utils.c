#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include "utils.h"

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

int getIntInput(const char *prompt) {
    char buffer[256];
    while (1) {
        readString(prompt, buffer, sizeof(buffer));
        char *end;
        errno = 0;
        long value = strtol(buffer, &end, 10);
        if (errno == 0 && *end == '\0' && end != buffer) {
            return (int)value;
        }
        printf("Invalid input. Please enter a whole number.\n");
    }
}

float getFloatInput(const char *prompt) {
    char buffer[256];
    while (1) {
        readString(prompt, buffer, sizeof(buffer));
        char *end;
        errno = 0;
        float value = strtof(buffer, &end);
        if (errno == 0 && *end == '\0' && end != buffer) {
            return value;
        }
        printf("Invalid input. Please enter a number.\n");
    }
}
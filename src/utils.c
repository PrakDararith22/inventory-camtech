#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
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


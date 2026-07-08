#ifndef UTILS_H
#define UTILS_H

int getIntInput(const char *prompt);
float getFloatInput(const char *prompt);
void readString(const char *prompt, char *out, int maxLen);
void toLowerCase(const char *src, char *dst);

#endif

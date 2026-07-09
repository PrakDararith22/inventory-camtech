#ifndef UTILS_H
#define UTILS_H

void readString(const char *prompt, char *out, int maxLen);
void toLowerCase(const char *src, char *dst);
int getIntInput(const char *prompt);
float getFloatInput(const char *prompt);

#endif
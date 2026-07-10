/**
 * @file    utils.h
 * @author  kelly
 * @version v1.0
 * @date    9-July-2026
 * @brief   Header for shared utility and input helpers.
 *
 * @attention
 * This project was developed as part of the Computer Fundamental course
 * at CamTech University.
 */

#ifndef UTILS_H
#define UTILS_H

void readString(const char *prompt, char *out, int maxLen);
void toLowerCase(const char *src, char *dst);
int getIntInput(const char *prompt);
float getFloatInput(const char *prompt);

#endif
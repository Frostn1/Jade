#define _CRT_SECURE_NO_WARNINGS

#ifndef TOOL_H
#define TOOL_H
#include <stdlib.h>
#include <string.h>
#include <io.h>
#include <stdio.h>
#include <conio.h>
#include <ctype.h>

char* readFile(char* filePath);
char* lower(char* string);

#endif // !TOOL_H
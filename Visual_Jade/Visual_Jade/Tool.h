#define _CRT_SECURE_NO_WARNINGS

#ifndef TOOL_H
#define TOOL_H
#include <stdlib.h>
#include <string.h>
#include <io.h>
#include <stdio.h>
#include <conio.h>
#include <ctype.h>

#define ASCII_ZERO '0'
#define ASCII_NINE '9'

#define SPACE_ASCII ' '
#define NEWLINE_ASCII '\n'

char* readFile(char* filePath);
char* lower(char* string);
int isNumeric(char* string);
int isSpace(char ch);
#endif // !TOOL_H
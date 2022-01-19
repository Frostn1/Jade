#define _CRT_SECURE_NO_WARNINGS

#ifndef TOOL_H
#define TOOL_H
#include <stdlib.h>
#include <string.h>
#include <io.h>
#include <stdio.h>
#include <conio.h>
#include <stdbool.h>
#include <ctype.h>

#define ASCII_ZERO '0'
#define ASCII_NINE '9'
#define ASCII_CAPITAL_A 'A'
#define ASCII_CAPITAL_Z 'Z'
#define ASCII_SMALL_A 'a'
#define ASCII_SMALL_Z 'z'
#define ASCII_TILDA '~'

#define ASCII_SPACE ' '
#define ASCII_NEWLINE '\n'
#define ASCII_TAB '\t'

// String manipulation
char* readFile(char* filePath);
char* lower(char* string);
char* slice(char* string, int start, int end);

// Boolean checks
bool isNumeric(char ch);
bool isNumericString(char* string);
bool isSpace(char ch);
bool isDigit(char ch);
bool isLetter(char ch);
bool isSpecial(char ch);
int isKeyword(char* keywords[], int size, char* lexeme);

#endif // !TOOL_H
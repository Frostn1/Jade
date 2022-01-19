#include "Tool.h"

char* readFile(char* filePath) {
    if (_access(filePath, 0) == -1) printf("file doesn't exist\n"); 
    FILE* filePointer = fopen(filePath,"r");
    if (!filePointer) printf("can't open file\n");
    char* buffer = 0;
    long length;
    fseek(filePointer, 0, SEEK_END);
    length = ftell(filePointer);
    fseek(filePointer, 0, SEEK_SET);
    buffer = calloc(length, length);
    if (buffer) fread(buffer, 1, length, filePointer);
    fclose(filePointer);
    return buffer;
}

char* lower(char* string) {
    if(!strcmp(string, "")) return string;
    int size = strlen(string);
    for(int i = 0; i < size; i++) {
        if(isupper(string[i])) 
            string[i] = string[i] + 32;
    }
    return string;
}

char* slice(char* string, int start, int end) {
    char* newString = (char*)malloc(sizeof(char) * (end - start + 1));
    strncpy(newString, string, end - start);
    newString[end - start] = '\0';
    return newString;
}


bool isNumeric(char ch) {
    return (ch < ASCII_ZERO || ch > ASCII_NINE);
}
bool isNumericString(char* string) {
    for (size_t i = 0; i < strlen(string); i++) {
        if (!isNumeric(string[i]))
            return false;
    }
    return true;
}

bool isSpace(char ch) {
    return ch == ASCII_SPACE ||
        ch == ASCII_NEWLINE  ||
        ch == ASCII_TAB;
}

bool isDigit(char ch) {
    return (ch >= ASCII_ZERO && ch <= ASCII_ZERO);
}

bool isLetter(char ch) {
    return (ch >= ASCII_CAPITAL_A && ch <= ASCII_CAPITAL_Z) ||
        (ch >= ASCII_SMALL_A && ch <= ASCII_SMALL_Z);
}

bool isSpecial(char ch) {
    return (isSpace(ch) ||
        (ch >= ASCII_SPACE && ch <= ASCII_TILDA &&
            !isDigit(ch) && !isLetter(ch)));
}

int isKeyword(char* keywords[], int size, char* lexeme) {
    for (size_t i = 0; i < size; i++) {
        if (!strcmp(keywords[i], lexeme))
            return i + 1;
    }
    return 0;
}

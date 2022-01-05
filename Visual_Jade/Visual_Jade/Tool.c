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

int isNumeric(char* string) {
    for (size_t i = 0; i < strlen(string); i++) {
        if (string[i] < ASCII_ZERO || string[i] > ASCII_NINE)
            return 0;
    }
    return 1;
}

int isSpace(char ch) {
    return ch == SPACE_ASCII ||
        ch == NEWLINE_ASCII;
}

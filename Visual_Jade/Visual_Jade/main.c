#include <stdio.h>
#include <stdlib.h>
#include "Tool.h"
#include "Lexer.h"

int main() {
	char* text = readFile("D:/Programming/Projects/Jade/exmp/PrintString.jd");
	int index = 0;
	scanNewToken(text, &index);
	return 0;
}
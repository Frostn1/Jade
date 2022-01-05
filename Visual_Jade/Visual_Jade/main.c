#include <stdio.h>
#include <stdlib.h>
#include "Compiler.h"

int main() {
	Compiler* comp = newCompiler(DEBUG_ON);
	char* text = readFile("main.jd");
	codeToInstructionArray(comp, text);
	return 0;
}
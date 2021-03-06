#include <stdio.h>
#include <stdlib.h>
#include "Compiler.h"

int main() {
	Compiler* comp = newCompiler(DEBUG_OFF);
	char* text = readFile("D:/Programming/Projects/Jade/exmp/PrintString.jd");
	codeToInstructionArray(comp, text);
	if (comp->error)
		fprintf(stderr, "ERROR: while matching terms\n");
	else
		runCompiler(comp);
	freeCompiler(comp);
	return 0;
}
#include "Compiler.h"

Compiler* newCompiler(DEBUG_OPTIONS debugFlag) {
	Compiler* comp = (Compiler*)malloc(sizeof(Compiler));
	comp->debug = debugFlag;
	comp->ip = 0;
	comp->sp = 0;
	comp->error = ERROR_OFF;
	return comp;
}

void runCompiler(Compiler* comp) {

}

void freeCompiler(Compiler* comp) {
	free(comp);
	return;
}



// Lexical
// Might end with comp having the error flag up, need to check after leaving function
void codeToInstructionArray(Compiler* comp, char* rawCode) {
	int startIndex = 0, endIndex = 0, ic = 0;
	char* word = NULL;
	for (size_t i = 0; i < strlen(rawCode); i++) {
		if (isSpace(rawCode[i]) && startIndex != endIndex) {
			word = (char*)malloc(endIndex - startIndex + 1);
			strncpy(word, &rawCode[startIndex], endIndex - startIndex);
			word[endIndex - startIndex] = '\0';
			if(comp->debug) printf("DEBUG: %s\n", word);
			ic = isInstruction(lower(word));
			if (ic-INSTRUCTION_EMPTY) comp->code[comp->ip++] = ic;
			else if (isNumeric(word)) comp->code[comp->ip++] = atoi(word);
			else {
				comp->error = ERROR_LEXICAL;
				return;
			}
			startIndex = endIndex = i;
		} else if(isSpace(rawCode[startIndex])) {
			startIndex = endIndex = i;
		} else {
			endIndex++;
		}
			
	}
}
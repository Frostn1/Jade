#include "Compiler.h"

Compiler* newCompiler(DEBUG_OPTIONS debugFlag) {
	Compiler* comp = (Compiler*)malloc(sizeof(Compiler));
	comp->debug = debugFlag;
	comp->ip = 0;
	comp->sp = 0;
	comp->error = ERROR_OFF;
	for (size_t i = 0; i < NUM_OF_REGISTERS; i++) {
		comp->Registers[i] = 0;
	}
	return comp;
}

void runCompiler(Compiler* comp) {
	comp->ip = 0;
	while (true) {
		switch (comp->code[comp->ip]) {
		case PUSH:
			comp->Stack[comp->sp++] = comp->code[++comp->ip];
			comp->ip++;
			break;
		case POP:
			comp->Registers[comp->code[comp->ip + 1]] = comp->Stack[--comp->sp];
			comp->ip += 2;
			break;
		case DROP:
			printf("%d", comp->code[comp->ip + 1]);
			comp->ip += 2;
			break;
		case MOV:
			comp->Registers[comp->code[comp->ip + 1]] = comp->code[comp->ip + 2];
			comp->ip += 3;
			break;
		case STP:
			return;
		}
	}
}

void freeCompiler(Compiler* comp) {
	free(comp);
	return;
}



// Lexical
// Might end with comp having the error flag up, need to check after leaving function
bool makeInstruction(Compiler* comp, int start, int end, char* raw) {
	char* word = NULL;
	int ic = 0, rc = 0;
	word = (char*)malloc(end - start + 1);
	strncpy(word, &raw[start], end - start);
	word[end - start] = '\0';
	if (comp->debug) printf("DEBUG: %s\n", word);
	ic = isInstruction(lower(word));
	rc = isRegister(lower(word));
	if (ic - INSTRUCTION_EMPTY) comp->code[comp->ip++] = ic;
	else if(rc - REGISTER_EMPTY) comp->code[comp->ip++] = rc;
	else if (isNumeric(word)) comp->code[comp->ip++] = atoi(word);
	else {
		comp->error = ERROR_LEXICAL;
		return false;;
	}
	return true;
}

void codeToInstructionArray(Compiler* comp, char* rawCode) {
	int startIndex = 0, endIndex = 0;
	
	for (size_t i = 0; i < strlen(rawCode); i++) {
		if ((isSpace(rawCode[i]) && startIndex != endIndex)) {
			if (!makeInstruction(comp, startIndex, endIndex, rawCode))
				return;
		}
		while(isSpace(rawCode[i])) {
			startIndex = endIndex = ++i;
		}
		endIndex++;
	}
	if (!makeInstruction(comp, startIndex, endIndex, rawCode))
		return;
}
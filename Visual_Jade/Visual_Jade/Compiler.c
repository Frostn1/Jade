#include "Compiler.h"

Compiler* newCompiler(DEBUG_OPTIONS debugFlag) {
	Compiler* comp = (Compiler*)malloc(sizeof(Compiler));
	comp->debug = debugFlag;
	comp->ip = 0, comp->sp = 0;
	comp->zf = 0;
	comp->error = ERROR_OFF;
	comp->amount = 0;
	for (size_t i = 0; i < NUM_OF_REGISTERS; i++) {
		comp->Registers[i] = -1;
	}
	comp->list = newLabelList();
	return comp;
}

void runCompiler(Compiler* comp) {
	comp->ip = 0;
	while (true) {
		switch (*comp->code[comp->ip]) {
		case PUSH:
			comp->Stack[comp->sp++] = *comp->code[++comp->ip];
			comp->ip++;
			break;
		case POP:
			comp->Registers[*comp->code[comp->ip + 1]] = comp->Stack[--comp->sp];
			comp->ip += 2;
			break;
		case PRT:
			printf("%d", comp->Registers[*comp->code[comp->ip + 1]]);
			comp->ip += 2;
			break;
		case CHR:
			printf("%c", comp->Registers[*comp->code[comp->ip + 1]]);
			comp->ip += 2;
			break;
		case MOV:
			comp->Registers[*comp->code[comp->ip + 1]] = *comp->code[comp->ip + 2];
			comp->ip += 3;
			break;
		case JMP:
			comp->ip = *comp->code[comp->ip + 1];
			break;
		case STACK:
			dumpStack(comp);
			comp->ip++;
			break;
		case REG:
			dumpRegisters(comp);
			comp->ip++;
			break;
		case CMP:
			comp->zf = comp->Registers[*comp->code[++comp->ip]] - comp->Stack[comp->sp - 1];
			comp->ip++;
			break;
		case JNE:
			comp->ip = !comp->zf ? comp->ip + 2 : *comp->code[comp->ip + 1];
			break;
		case JE:
			comp->ip = !comp->zf ? comp->ip + 2 : *comp->code[comp->ip + 1];
			break;
		case INC:
			comp->Registers[*comp->code[comp->ip + 1]]++;
			comp->ip += 2;
			break;
		case DEC:
			comp->Registers[*comp->code[comp->ip + 1]]--;
			comp->ip += 2;
			break;
		case DROP:
			comp->sp -= *comp->code[++comp->ip];
			comp->ip++;
		case CALL:
			comp->Stack[comp->sp++] = comp->ip + 2;
			comp->ip = *comp->code[comp->ip + 1];
			break;
		case RET:
			comp->ip = comp->Stack[--comp->sp];
			break;
		case STP:
			return;
		}
	}
}

void freeCompiler(Compiler* comp) {
	freeLabelList(comp->list);
	for (size_t i = 0; i < comp->amount; i++) {
		if(*comp->code[i] > 0)
			free(comp->code[i]);
	}
	free(comp);
	return;
}

void dumpStack(Compiler* comp) {
	putchar('\n');
	for (size_t i = 0; i < comp->sp; i++) {
		printf("0x%x ... %d\n", &comp->Stack[i], comp->Stack[i]);
	}
	return;
}

void dumpRegisters(Compiler* comp) {
	printf("\nReg Dump:\n");
	for (size_t i = 0; i < sizeof(comp->Registers) / sizeof(int); i++) {
		printf("%s <-> %d\n", RegisterArray[i], comp->Registers[i]);
	}
	return;
}


void move(int* array[], int index, int num) {
	array[index] = (int*)malloc(sizeof(int));
	*array[index] = num;
}

// Lexical
// Might end with comp having the error flag up, need to check after leaving function
bool makeInstruction(Compiler* comp, int start, int end, char* raw) {
	char* word = NULL;
	// ic - Instruction
	// rc - Register
	// lc - Label
	int ic = 0, rc = 0, lc = 0;
	word = (char*)malloc(end - start + 1);
	strncpy(word, &raw[start], end - start);
	word[end - start] = '\0';
	if (comp->debug) printf("DEBUG: %s\n", word);
	ic = isInstruction(lower(word));
	rc = isRegister(lower(word));
	lc = isLabel(lower(word));
	if (lc && addLabel(comp->list, newLabel(lower(word), comp->ip))) return true;
	else if (hasLabel(comp->list, lower(word))) comp->code[comp->ip] = &getLabel(comp->list, lower(word))->ip;
	else if (ic - INSTRUCTION_EMPTY) move(comp->code, comp->ip, ic);
	else if (rc - REGISTER_EMPTY) move(comp->code, comp->ip, rc);
	else if (isNumeric(word)) move(comp->code, comp->ip, atoi(word));
	else {
		comp->error = ERROR_LEXICAL;
		return false;
	}
	comp->ip++;
	comp->amount++;
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
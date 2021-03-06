#include "Compiler.h"

Compiler* newCompiler(DEBUG_OPTIONS debugFlag) {
	Compiler* comp = (Compiler*)malloc(sizeof(Compiler));
	comp->debug = debugFlag;
	comp->zf = 0;
	comp->error = ERROR_OFF;
	comp->amount = 0;
	for (size_t i = 0; i < NUM_OF_REGISTERS; i++) {
		comp->Registers[i] = -1;
	}
	comp->Registers[ip] = 0, comp->Registers[rsp] = 0;
	comp->list = newLabelList();
	return comp;
}

void runCompiler(Compiler* comp) {
	if (!validateLabels(comp->list)) return;
	comp->Registers[ip] = 0;
	while (true) {
		switch (*comp->code[comp->Registers[ip]]) {
		case PUSH:
			comp->Stack[comp->Registers[rsp]++] = *comp->code[++comp->Registers[ip]];
			comp->Registers[ip]++;
			break;
		case POP:
			*comp->code[comp->Registers[ip] + 1] = comp->Stack[--comp->Registers[rsp]];
			comp->Registers[ip] += 2;
			break;
		case PRT:
			printf("%d", *comp->code[comp->Registers[ip] + 1]);
			comp->Registers[ip] += 2;
			break;
		case CHR:
			printf("%c", *comp->code[comp->Registers[ip] + 1]);
			comp->Registers[ip] += 2;
			break;
		case MOV:
			*comp->code[comp->Registers[ip] + 1] = *comp->code[comp->Registers[ip] + 2];
			comp->Registers[ip] += 3;
			break;
		case JMP:
			comp->Registers[ip] = *comp->code[comp->Registers[ip] + 1];
			break;
		case STACK:
			dumpStack(comp);
			comp->Registers[ip]++;
			break;
		case REG:
			dumpRegisters(comp);
			comp->Registers[ip]++;
			break;
		case CMP:
			comp->zf = *comp->code[comp->Registers[ip] + 1] - *comp->code[comp->Registers[ip] + 2];
			comp->Registers[ip] += 3;
			break;
		case JNE:
			comp->Registers[ip] = !comp->zf ? comp->Registers[ip] + 2 : *comp->code[comp->Registers[ip] + 1];
			break;
		case JE:
			comp->Registers[ip] = comp->zf ? comp->Registers[ip] + 2 : *comp->code[comp->Registers[ip] + 1];
			break;
		case INC:
			(*comp->code[comp->Registers[ip] + 1])++;
			comp->Registers[ip] += 2;
			break;
		case DEC:
			(*comp->code[comp->Registers[ip] + 1])--;
			comp->Registers[ip] += 2;
			break;
		case DROP:
			*comp->code[comp->Registers[ip] + 1] = comp->Stack[comp->Registers[rsp] - *comp->code[comp->Registers[ip] + 2]];
			comp->Registers[ip] += 3;
			break;
		case LIFT:
			comp->Stack[comp->Registers[rsp] - *comp->code[comp->Registers[ip] + 2]] = *comp->code[comp->Registers[ip] + 1];
			comp->Registers[ip] += 3;
			break;
		case CALL:
			comp->Stack[comp->Registers[rsp]++] = comp->Registers[ip] + 2;
			comp->Registers[ip] = *comp->code[comp->Registers[ip] + 1];
			break;
		case RET:
			comp->Registers[ip] = comp->Stack[--comp->Registers[rsp]];
			break;
		case JG:
			comp->Registers[ip] = comp->zf <= 0 ? comp->Registers[ip] + 2 : *comp->code[comp->Registers[ip] + 1];
			break;
		case JL:
			comp->Registers[ip] = comp->zf >= 0 ? comp->Registers[ip] + 2 : *comp->code[comp->Registers[ip] + 1];
			break;
		case JLE:
			comp->Registers[ip] = comp->zf > 0 ? comp->Registers[ip] + 2 : *comp->code[comp->Registers[ip] + 1];
			break;
		case JGE:
			comp->Registers[ip] = comp->zf < 0 ? comp->Registers[ip] + 2 : *comp->code[comp->Registers[ip] + 1];
			break;
		case ADD:
			*comp->code[comp->Registers[ip] + 1] += *comp->code[comp->Registers[ip] + 1];
			comp->Registers[ip] += 3;
			break;
		case SUB:
			*comp->code[comp->Registers[ip] + 1] -= *comp->code[comp->Registers[ip] + 1];
			comp->Registers[ip] += 3;
			break;
		case STP:
			return;
		default:
			fprintf(stderr, "Unknown sub routine < %s > with code %d\n", InstructionArray[*comp->code[comp->Registers[ip]]], *comp->code[comp->Registers[ip]]);
			return;
		}
	}
}

void freeCompiler(Compiler* comp) {
	freeLabelList(comp->list);
	/*for (size_t i = 0; i < comp->amount; i++) {
		if(*comp->code[i] > 0)
			free(comp->code[i]);
	}*/
	free(comp);
	return;
}

void dumpStack(Compiler* comp) {
	putchar('\n');
	for (size_t i = 0; i < comp->Registers[rsp]; i++) {
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
	if (lc && addLabel(comp->list, newLabel(lower(word), comp->Registers[ip]))) return true;
	else if (ic - INSTRUCTION_EMPTY) move(comp->code, comp->Registers[ip], ic);
	else if (rc - REGISTER_EMPTY) comp->code[comp->Registers[ip]] = &comp->Registers[rc];
	else if (isNumeric(word)) move(comp->code, comp->Registers[ip], atoi(word));
	else if (hasLabel(comp->list, lower(word), LOOKAHEAD_ON)) comp->code[comp->Registers[ip]] = &getLabel(comp->list, lower(word))->ip;
	else {
		comp->error = ERROR_LEXICAL;
		return false;
	}
	comp->Registers[ip]++;
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
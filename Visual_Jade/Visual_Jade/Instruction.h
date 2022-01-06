#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include "Register.h"

#include <string.h>

#define INSTRUCTION_EMPTY -1

typedef enum {
	PUSH,
	POP,
	PRT,
	MOV,
	STP,
	CHR,
	JMP,
	STACK,
	REG,
	NUM_OF_INSTRUCTION,
}Instruction;

extern char* InstructionArray[];

int isInstruction(char* word);
#endif // !INSTRUCTION_H

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
	CMP,
	JNE,
	JE,
	INC,
	DEC,
	CALL,
	RET,
	DROP,
	LIFT,
	JL,
	JLE,
	JG,
	JGE,
	SUB,
	ADD,
	NUM_OF_INSTRUCTION,
}Instruction;

extern char* InstructionArray[];

int isInstruction(char* word);
#endif // !INSTRUCTION_H

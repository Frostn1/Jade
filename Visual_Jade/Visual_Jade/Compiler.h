#ifndef COMPILER_H
#define COMPILER_H

#include <stdlib.h>
#include <stdio.h>

#include "Register.h"
#include "Instruction.h"

#define STACK_SIZE 256
#define MAX_CODE_SIZE 1024

typedef enum {
	DEBUG_OFF,
	DEBUG_ON
}DEBUG_OPTIONS;

typedef enum {
	ERROR_OFF,
	LEXICAL_ERROR,
	VALUE_ERROR,
}ERROR_OPTIONS;

typedef struct Compiler_16B {
	int Registers[NUM_OF_REGISTERS];
	int Stack[STACK_SIZE];
	int code[MAX_CODE_SIZE];

	// Special Registers
	int sp;
	int ip;

	// Special flags
	int error;
	int debug;


}Compiler;

Compiler* newCompiler(DEBUG_OPTIONS debugFlag);
void runCompiler(Compiler* comp);
void freeCompiler(Compiler* comp);
#endif // !COMPILER_H

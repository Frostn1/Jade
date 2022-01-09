#define _CRT_SECURE_NO_WARNINGS

#ifndef COMPILER_H
#define COMPILER_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "Register.h"
#include "Instruction.h"
#include "Label.h"
#include "Tool.h"

#define STACK_SIZE 256
#define MAX_CODE_SIZE 1024

typedef enum {
	DEBUG_OFF,
	DEBUG_ON
}DEBUG_OPTIONS;


typedef enum {
	ERROR_OFF,
	ERROR_LEXICAL,
	ERROR_VALUE,
}ERROR_OPTIONS;

typedef struct Compiler_16B {
	int Registers[NUM_OF_REGISTERS];
	int Stack[STACK_SIZE];
	int* code[MAX_CODE_SIZE];
	int amount;

	// Special Flags
	int error;
	int debug;

	// Conditional Flags
	int zf;

	LabelList* list;

}Compiler;

// Full Compiler
Compiler* newCompiler(DEBUG_OPTIONS debugFlag);
void runCompiler(Compiler* comp);
void freeCompiler(Compiler* comp);

void dumpRegisters(Compiler* comp);
void dumpStack(Compiler* comp);

void move(int* array[], int index, int num);

// Lexical
bool makeInstruction(Compiler* comp, int start, int end, char* raw);
void codeToInstructionArray(Compiler* comp, char* rawCode);
#endif // !COMPILER_H

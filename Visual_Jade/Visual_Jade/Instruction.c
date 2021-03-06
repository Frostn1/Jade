#include "Instruction.h"


/*
typedef enum {
	PUSH,
	POP,
	DROP,
	MOV,
	STP,
	NUM_OF_INSTRUCTION,
}Instruction;
*/
char* InstructionArray[NUM_OF_INSTRUCTION] = {
	"push",
	"pop",
	"prt",
	"mov",
	"stp",
	"chr",
	"jmp",
	"stack",
	"reg",
	"cmp",
	"jne",
	"je",
	"inc",
	"dec",
	"call",
	"ret",
	"drop",
	"lift",
	"jl",
	"jle",
	"jg",
	"jge",
	"sub",
	"add"
};


int isInstruction(char* word) {
	for (size_t i = 0; i < NUM_OF_INSTRUCTION ; i++) {
		if (!strcmp(InstructionArray[i], word))
			return i;
	}
	return INSTRUCTION_EMPTY;
}
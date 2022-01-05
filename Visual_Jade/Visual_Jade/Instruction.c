#include "Instruction.h"


/*
typedef enum {
	PUSH,
	POP,
	DROP,
	MOV,
	NUM_OF_INSTRUCTION,
}Instruction;
*/
char* InstructionArray[NUM_OF_INSTRUCTION + NUM_OF_REGISTERS] = {
	"push",
	"pop",
	"drop",
	"mov",
	"dx",
	"ex",
	"fx",
};

int isInstruction(char* word) {
	for (size_t i = 0; i < NUM_OF_INSTRUCTION; i++) {
		if (!strcmp(InstructionArray[i], word))
			return i;
	}
	return INSTRUCTION_EMPTY;
}
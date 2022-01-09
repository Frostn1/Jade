#include "Register.h"

char* RegisterArray[NUM_OF_REGISTERS] = {
	"eax",
	"ebx",
	"ecx",
	"edx",
	"rbp",
	"rsp",
	"dx",
	"ex",
	"fx",
};



int isRegister(char* word) {
	for (size_t i = 0; i < NUM_OF_REGISTERS; i++) {
		if (!strcmp(RegisterArray[i], word))
			return i;
	}
	return REGISTER_EMPTY;
}
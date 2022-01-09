#ifndef REGISTER_H
#define REGISTER_H

#include <string.h>

#define REGISTER_EMPTY -1

typedef enum {
	eax,
	ebx,
	ecx,
	edx,
	rbp,
	rsp,
	dx,
	ex,
	fx,
	NUM_OF_REGISTERS
}Register;



extern char* RegisterArray[];

int isRegister(char* word);
#endif // !REGISTER_H

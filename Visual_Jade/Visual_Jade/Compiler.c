#include "Compiler.h"

Compiler* newCompiler(DEBUG_OPTIONS debugFlag) {
	Compiler* comp = (Compiler*)malloc(sizeof(Compiler));
	comp->debug = debugFlag;
	comp->ip = 0;
	comp->sp = 0;
	comp->error = ERROR_OFF;
	
}

void runCompiler(Compiler* comp) {

}

void freeCompiler(Compiler* comp) {

}
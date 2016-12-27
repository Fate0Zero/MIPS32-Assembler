#include "Function.h"

#define NUMRECORDS 10

static Function FunctionTable[NUMRECORDS] = {
	{"100000", "add"},
	{"100100", "and"},
	{"100101", "or"},
	{"001100", "syscall"},
	{"100111", "nor"},
	{"100010", "sub"},
	{"101010", "slt"},
	{"000010", "mul"},
	{"000000", "sll"},
	{"000011", "sra"}
	
};

const Function* FindF(const char* const code) {
	for (int i = 0; i < NUMRECORDS; i++) {
		if (strcmp(code, FunctionTable[i].mnemonic) == 0) {
			return &FunctionTable[i];
		}
	}
	return NULL;
}

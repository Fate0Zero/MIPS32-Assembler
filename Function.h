// the static lookup table for function part
// to determine the type of R-type instruction

#ifndef FUNCTION_H
#define FUNCTION_H
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>

// define _Function structure

struct _Function {
	char* function;
	char* mnemonic;
};

typedef struct _Function Function;

const Function* FindF(const char* const code);

#endif

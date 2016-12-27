// the static lookup table for operation code part
// to determine the type of instruction (R-type or I-type)

#ifndef OPERATION_H
#define OPERATION_H
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>

// define _Operation structure

struct _Operation {
	char* code;
	char* mnemonic;
};

typedef struct _Operation Operation;

const Operation* Find(const char* const operation);

#endif

#include "Operation.h"

#define NUMRECORDS 24

static Operation OperationTable[NUMRECORDS] = {
	{"000000", "add"},
	{"000000", "and"},
	{"000000", "or"},
	{"000000", "sub"},
	{"000000", "slt"},
	{"011100", "mul"},
	{"000000", "sll"},
	{"000000", "sra"},
	{"000010", "j"},
	{"000110", "blez"},
	{"000001", "bltz"},
	{"001010", "slti"},
	{"101011", "sw"},
	{"001001", "li"},
	{"001000", "addi"},
	{"001001", "addiu"},
	{"000000", "nor"},
	{"001000", "la"},
	{"000100", "beq"},
	{"000101", "bne"},
	{"001100", "andi"},
	{"001111", "lui"},
	{"100011", "lw"},
	{"001101", "ori"}
};

const Operation* Find(const char* const operation) {
	for (int i = 0; i < NUMRECORDS; i++) {
		if (strcmp(operation, OperationTable[i].mnemonic) == 0) {
			return &OperationTable[i];
		}
	}
	return NULL;
}

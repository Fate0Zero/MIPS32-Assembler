// the static lookup table for registers

#ifndef REGISTER_H
#define REGISTER_H
#include <inttypes.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

// define _Register structure

struct _Register {
	uint8_t number;
	char* Reg;
	char* name;
};

typedef struct _Register Register;

const Register* FindR(const char* const reg);



#endif

#include "ASMParser.h"
#include <stdlib.h>
#include <stdio.h>

// Add any needed include directives here
#include "Operation.h"
#include "Function.h"
#include "Register.h"
#include "ParseResult.h"
#include <string.h>

// Add declarations of any static helper functions here.


/**  Breaks up the given MIPS32 assembly instruction and creates a proper 
 *   ParseResult pch storing information about that instruction.
 * 
 *   Pre:  pASM points to an array holding the bits (as chars) of a
 *         syntactically valid assembly instruction, whose mnemonic is
 *         one of the following:
 *             add  addi  and  andi  lui  lw  or  ori  sub
 * 
 *   Returns:
 *         A pointer to a proper ParseResult pch whose fields have been
 *         correctly initialized to correspond to the target of pASM.
 */



ParseResult* parseASM(const char* const pASM, int currentLine) {
	const char* temp = pASM;
	ParseResult* result = (ParseResult*) calloc(1, sizeof(ParseResult));
	char* pch = strtok(temp, " ,\t()");
	result->Mnemonic = calloc(6, sizeof(char));
	strcpy(result->Mnemonic, pch);
	if (strcmp(result->Mnemonic, "add") == 0 ||
	    strcmp(result->Mnemonic, "and") == 0 ||
	    strcmp(result->Mnemonic, "or") == 0 ||
	    strcmp(result->Mnemonic, "sub") == 0 ||
	 	strcmp(result->Mnemonic, "slt") == 0 ||
		strcmp(result->Mnemonic, "mul") == 0 ||
	    strcmp(result->Mnemonic, "nor") == 0) {
		result->Funct = (char*) calloc(1, 7*sizeof(char*));
		strcpy(result->Funct, FindF(result->Mnemonic)->function);
		result->Opcode = (char*) calloc(1, 7*sizeof(char*));
		strcpy(result->Opcode, Find(result->Mnemonic)->code);		
		pch = strtok (NULL, " ,\t()");
		result->rdName = (char*) calloc(1, 7*sizeof(char*));
		strcpy(result->rdName, pch);
		result->rd = FindR(result->rdName)->number;
		result->RD = (char*) calloc(1, 6*sizeof(char*));
		strcpy(result->RD, FindR(result->rdName)->Reg);
		pch = strtok (NULL, " ,\t()");
		result->rsName = (char*) calloc(1, 7*sizeof(char*));
		strcpy(result->rsName, pch);
		result->rs = FindR(result->rsName)->number;
		result->RS = (char*) calloc(1, 6*sizeof(char*));
		strcpy(result->RS, FindR(result->rsName)->Reg);
		pch = strtok (NULL, " ,\t()");
		result->rtName = (char*) calloc(1, 7*sizeof(char*));
		strcpy(result->rtName, pch);
		result->rt = FindR(result->rtName)->number;
		result->RT = (char*) calloc(1, 6*sizeof(char*));
		strcpy(result->RT, FindR(result->rtName)->Reg);
		result->Imm = 0;
		result->IMM = NULL;
	}
	else if (strcmp(result->Mnemonic, "sll") == 0 ||
		 strcmp(result->Mnemonic, "sra") == 0) {
		result->rdName = calloc(7, sizeof(char));
		pch = strtok(NULL, " ,\t()");
		strcpy(result->rdName, pch);
		result->rtName = calloc(7, sizeof(char));
		pch = strtok(NULL, " ,\t()");
		strcpy(result->rtName, pch);
		result->Opcode = calloc(7, sizeof(char));
		result->Funct = calloc(7, sizeof(char));
		result->RD = calloc(6, sizeof(char));
		result->RS = calloc(6, sizeof(char));
		result->RT = calloc(6, sizeof(char));
		strcpy(result->Opcode, Find(result->Mnemonic)->code);
		strcpy(result->Funct, FindF(result->Mnemonic)->function);
		strcpy(result->RD, FindR(result->rdName)->Reg);
		strcpy(result->RS, "00000");
		strcpy(result->RT, FindR(result->rtName)->Reg);
		result->Shift = calloc(6, sizeof(char));
		pch = strtok(NULL, " ,\t()");
		int number = atoi(pch);
		char* f = DetoBi(number, 5);
		strcpy(result->Shift, f);
		free(f);
	}
	else if (strcmp(result->Mnemonic, "nop") == 0) {
			result->Opcode = calloc(7, sizeof(char));
			strcpy(result->Opcode, "000000");
			result->RS = calloc(6, sizeof(char));
			result->RT = calloc(6, sizeof(char));
			strcpy(result->RS, "00000");
			strcpy(result->RT, "00000");
			result->IMM = calloc(17, sizeof(char));
			strcpy(result->IMM, "0000000000000000");
		}
		
		else if (strcmp(result->Mnemonic, "addi") == 0
			|| strcmp(result->Mnemonic, "andi") == 0
			|| strcmp(result->Mnemonic, "slti") == 0
			|| strcmp(result->Mnemonic, "addiu") == 0
			|| strcmp(result->Mnemonic, "ori") == 0) {
		result->Opcode = (char*) calloc(1, 7*sizeof(char*));
		strcpy(result->Opcode, Find(result->Mnemonic)->code);
		pch = strtok (NULL, " ,\t()");
		result->rtName = (char*) calloc(1, 7*sizeof(char*));
		strcpy(result->rtName, pch);
		result->rt = FindR(result->rtName)->number;
		result->RT = (char*) calloc(1, 6*sizeof(char*));
		strcpy(result->RT, FindR(result->rtName)->Reg);		
		pch = strtok (NULL, " ,\t()");
		result->rsName = (char*) calloc(1, 7*sizeof(char*));
		strcpy(result->rsName, pch);
		result->rs = FindR(result->rsName)->number;
		result->RS = (char*) calloc(1, 6*sizeof(char*));
		strcpy(result->RS, FindR(result->rsName)->Reg);		
		result->rdName = NULL;
		result->RD = NULL;
		result->rd = 255;
		pch = strtok (NULL, " ,\t()");
		result->Imm = atoi(pch);
		result->IMM = (char*) calloc(1, 17*sizeof(char*));
		int n = atoi(pch);
		char* f = DetoBi(n, 16);
		strcpy(result->IMM, f);
		free(f);
		}
	else if (strcmp(result->Mnemonic, "lui") == 0 ||
		    strcmp(result->Mnemonic, "li") == 0) {
			result->rtName = (char*) calloc(1, 7*sizeof(char*));
		pch = strtok(NULL, " ,\t()");
		strcpy(result->rtName, pch);
		result->rsName = NULL;
		result->rdName = NULL;
		result->RD = NULL;
		result->Funct = NULL;
		result->rs = 0;
		result->rd = 255;
		result->rt = FindR(result->rtName)->number;
		result->IMM = (char*) calloc(1, 17*sizeof(char*));
		pch = strtok(NULL, " ,\t()");
		result->Imm = atoi(pch);
		result->Opcode = (char*) calloc(1, 7*sizeof(char*));
		result->RT = (char*) calloc(1, 6*sizeof(char*));
		result->RS = (char*) calloc(1, 6*sizeof(char*));
		strcpy(result->RS,"00000");
		strcpy(result->Opcode, Find(result->Mnemonic)->code);
		strcpy(result->RT, FindR(result->rtName)->Reg);

		char* f = DetoBi(atoi(pch), 16);
		strcpy(result->IMM, f);
		free(f);
	}
		else if (strcmp(result->Mnemonic, "lw") == 0 ||
			 strcmp(result->Mnemonic, "sw") == 0) {
			result->rdName = NULL;
			result->rsName = calloc(7, sizeof(char));
			result->rtName = calloc(7, sizeof(char));
			result->IMM = calloc(17, sizeof(char));
			pch = strtok(NULL, " ,\t()");
			strcpy(result->rtName, pch);
			pch = strtok(NULL, " ,\t()");
			char* label = 	calloc(7, sizeof(char));
			strcpy(label, pch);
			pch = strtok(NULL, " ,\t()");
			if (pch == NULL) {
				strcpy(result->rsName, "$zero");
				FILE* input = fopen("symbol.txt", "r");
				char line[100];
				while (fgets(line, 100, input) != NULL) {
					if (strstr(line, label) != NULL) {
						char* label = strtok(line, ":  ");
						int number = (int)strtol(label, NULL, 0);
						char* f = DetoBi(number, 16);
						strcpy(result->IMM, f);
						free(f);
						break;
					}
				}
				fclose(input);
				free(label);
			}
			else {
				strcpy(result->rsName, pch);
				int number = atoi(label);
				char* f = DetoBi(number, 16);
				strcpy(result->IMM, f);
				free(f);
				free(label);
			}
			result->Opcode = calloc(7, sizeof(char));
			result->RS = calloc(6, sizeof(char));
			result->RT = calloc(6, sizeof(char));
			strcpy(result->Opcode, Find(result->Mnemonic)->code);
			strcpy(result->RS, FindR(result->rsName)->Reg);
			strcpy(result->RT, FindR(result->rtName)->Reg);
		}
		else if (strcmp(result->Mnemonic, "la") == 0) {
			result->Opcode = (char*) calloc(1, 7*sizeof(char*));
			strcpy(result->Opcode, Find(result->Mnemonic)->code);
			result->rsName = (char*) calloc(1, 7*sizeof(char*));
			result->rtName = (char*) calloc(1, 7*sizeof(char*));
			strcpy(result->rsName, "$zero");
			pch = strtok(NULL, " ,\t()");
			strcpy(result->rtName, pch);
			pch = strtok(NULL, " ,\t()");
			result->RS = (char*) calloc(1, 6*sizeof(char*));
			result->RT = (char*) calloc(1, 6*sizeof(char*));
			strcpy(result->RS, FindR(result->rsName)->Reg);
			strcpy(result->RT, FindR(result->rtName)->Reg);
			result->IMM = (char*) calloc(1, 17*sizeof(char*));
			FILE* input = fopen("symbol.txt", "r");
			char line[100];
			while (fgets(line, 100, input) != NULL) {
				if (strstr(line,pch) != NULL) {
					char* label = strtok(line, "  ");
					int number = (int)strtol(label, NULL, 0);

					char* f = DetoBi(number, 16);
					strcpy(result->IMM, f);
					free(f);
				break;
				}
			}
			fclose(input);
		}
		else if (strcmp(result->Mnemonic, "beq") == 0 ||
			 strcmp(result->Mnemonic, "bne") == 0) {
			result->Opcode = (char*) calloc(1, 7*sizeof(char*));
			strcpy(result->Opcode, Find(result->Mnemonic)->code);
			result->rsName = (char*) calloc(1, 7*sizeof(char*));
			result->rtName = (char*) calloc(1, 7*sizeof(char*));
			pch = strtok(NULL, " ,\t()");
			strcpy(result->rsName, pch);
			pch = strtok(NULL, " ,\t()");
			strcpy(result->rtName, pch);
			result->RS = (char*) calloc(1, 6*sizeof(char*));
			result->RT = (char*) calloc(1, 6*sizeof(char*));
			strcpy(result->RS, FindR(result->rsName)->Reg);
			strcpy(result->RT, FindR(result->rtName)->Reg);
			result->IMM = (char*) calloc(1, 17*sizeof(char*));
			pch = strtok(NULL, " ,\t()");
			FILE* input = fopen("symbol.txt", "r");
			char line[100];
			while (fgets(line, 100, input) != NULL) {
				if (strstr(line, pch) != NULL) {
					char* label = strtok(line, "  ");
					int number = (int)strtol(label, NULL, 0);

					char* f = DetoBi((number / 4) - currentLine - 1, 16);
					strcpy(result->IMM, f);
					free(f);
				}
			}
			fclose(input);
		}
		else if (strcmp(result->Mnemonic, "blez") == 0 ||
			 strcmp(result->Mnemonic, "bltz") == 0) {
			result->Opcode = calloc(7, sizeof(char));
			strcpy(result->Opcode, Find(result->Mnemonic)->code);
			result->rsName = calloc(7, sizeof(char));
			pch = strtok(NULL, " ,\t()");
			strcpy(result->rsName, pch);
			result->RS = calloc(6, sizeof(char));
			strcpy(result->RS, FindR(result->rsName)->Reg);
			result->RT = calloc(6, sizeof(char));
			strcpy(result->RT, "00000");
			result->IMM = calloc(17, sizeof(char));
			pch = strtok(NULL, " ,\t()");
			FILE* input = fopen("symbol.txt", "r");
			char line[100];
			while(fgets(line, 100, input) != NULL) {
				if (strstr(line, pch) != NULL) {
					char* lab = strtok(line, ":  ");
					int n = (int)strtol(lab, NULL, 0);
					int j = (n / 4) - currentLine - 1;
					char* f = DetoBi(j, 16);
					strcpy(result->IMM, f);			
					free(f);		
				}
			}
			fclose(input);
		}
		else if (strcmp(result->Mnemonic, "j") == 0) {
			result->Opcode = calloc(7, sizeof(char));
			strcpy(result->Opcode, Find(result->Mnemonic)->code);
			result->IMM = calloc(27, sizeof(char));
			pch = strtok(NULL, " ,\t()");
			FILE* input = fopen("symbol.txt", "r");
			char line[100];
			while (fgets(line, 100, input) != NULL) {
				if (strstr(line, pch) != NULL) {
					char* label = strtok(line, ":  ");
					int number = (int)strtol(label, NULL, 0);
					int jump = number / 4;
					char* f = DetoBi(jump, 26);
					strcpy(result->IMM, f);
					free(f);
				}
			}
			fclose(input);
		}
		else if (strcmp(result->Mnemonic, "syscall") == 0) {
			result->rdName = NULL;
			result->rsName = NULL;
			result->rtName = NULL;
			result->Imm = 0;
			result->rd = 0;
			result->rs = 0;
			result->rt = 0;
			result->Opcode = (char*) calloc(1, 7*sizeof(char*));
			strcpy(result->Opcode, "000000");
			result->Funct = (char*) calloc(1, 7*sizeof(char*));
			strcpy(result->Funct, FindF(result->Mnemonic)->function);
			result->RD = NULL;
			result->RS = NULL;
			result->RT = NULL;
			result->IMM = NULL;
		}
		else if (strcmp(result->Mnemonic, "nop") == 0) {
			result->Opcode = calloc(7, sizeof(char));
			strcpy(result->Opcode, "000000");
			result->RS = calloc(6, sizeof(char));
			result->RT = calloc(6, sizeof(char));
			strcpy(result->RS, "00000");
			strcpy(result->RT, "00000");
			result->IMM = calloc(17, sizeof(char));
			strcpy(result->IMM, "0000000000000000");
		}
		
		else if (strcmp(result->Mnemonic, "addi") == 0
			|| strcmp(result->Mnemonic, "andi") == 0
			|| strcmp(result->Mnemonic, "slti") == 0
			|| strcmp(result->Mnemonic, "addiu") == 0
			|| strcmp(result->Mnemonic, "ori") == 0) {
		result->Opcode = (char*) calloc(1, 7*sizeof(char*));
		strcpy(result->Opcode, Find(result->Mnemonic)->code);
		pch = strtok (NULL, " ,\t()");
		result->rtName = (char*) calloc(1, 7*sizeof(char*));
		strcpy(result->rtName, pch);
		result->rt = FindR(result->rtName)->number;
		result->RT = (char*) calloc(1, 6*sizeof(char*));
		strcpy(result->RT, FindR(result->rtName)->Reg);		
		pch = strtok (NULL, " ,\t()");
		result->rsName = (char*) calloc(1, 7*sizeof(char*));
		strcpy(result->rsName, pch);
		result->rs = FindR(result->rsName)->number;
		result->RS = (char*) calloc(1, 6*sizeof(char*));
		strcpy(result->RS, FindR(result->rsName)->Reg);		
		result->rdName = NULL;
		result->RD = NULL;
		result->rd = 255;
		pch = strtok (NULL, " ,\t()");
		result->Imm = atoi(pch);
		result->IMM = (char*) calloc(1, 17*sizeof(char*));
		int n = atoi(pch);
		char* f = DetoBi(n, 16);
		strcpy(result->IMM, f);
		free(f);
		}
	
	return result;
}



char* DetoBi(int number, int byte) {
	char* result = calloc(byte + 1, sizeof(char));
	int count;
	int num;
	for (count = byte - 1; count >= 0; count--) {
		num = number >> count;
		if (num & 1) {
			result[byte - 1 - count] = '1';
		}
		else {
			result[byte - 1 - count] = '0';
		}
	}
	return result;
}
	


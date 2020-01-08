#ifndef __CODEGEN_H
#define __CODEGEN_H
#include <stdint.h>
#define NBYTE_NO_PARAM 2
#define NBYTE_ONE_PARAM 6

enum Opcodes
{
	OPC_NOP,
	OPC_PUSH,
	OPC_ADD,
	OPC_SUB,
	OPC_MUL,
	OPC_DIV,
	OPC_ADDC,
	OPC_SUBC,
	OPC_INC,
	OPC_DEC,
	OPC_SWAP,
	OPC_XOR,
	OPC_AND,
	OPC_OR,
	OPC_NOT,
	OPC_CALL,
	OPC_PUSHPC,
	OPC_JMP,
	OPC_RET,
	OPC_REF,
	OPC_DUP,
	OPC_MOD,
	OPC_CMP,
	OPC_JMPEQ,
	OPC_JMPLT,
	OPC_JMPGT,
	OPC_JMPLE,
	OPC_JMPGE,
	OPC_JMPAB,
	OPC_JMPBL,
	OPC_JMPAE,
	OPC_JMPBE,
	OPC_JMPNE,
	OPC_DIVMOD,
	OPC_ADDSP,
	OPC_SUBSP,
	OPC_INCSP,
	OPC_DECSP,
	OPC_UNREF,
	OPC_PUSHBP,
	OPC_POPBP,
	OPC_PUSHALL,
	OPC_POPALL,
	OPC_HALT,
	OPC_PUSHFLAGS,
	OPC_POPFLAGS,
	OPC_REFBP,
	OPC_UNREFBP,
	OPC_INT,
	OPC_OUT,
	OPC_IN,
	OPC_PUSH_HW_FLAGS
};

void code_gen_no_arg(uint8_t *code, enum Opcodes opcode, uint32_t *addr);
void code_out(const char *output_file, uint8_t *code, uint32_t byte);
void code_gen_one_arg(uint8_t *code, enum Opcodes opcode, uint32_t param, uint32_t *addr);

#endif
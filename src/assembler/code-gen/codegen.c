#include <stdio.h>
#include "../../include/code-gen/codegen.h"

void code_gen_no_arg(uint8_t *code, enum Opcodes opcode, uint32_t *addr)
{
	code[*addr] = (opcode&0xff00)<<8;
	*addr += 1;
	code[*addr] = (opcode&0x00ff);
	*addr += 1;
}

void code_out(char *fname, uint8_t *code, uint32_t byte)
{
	FILE *fp = fopen(fname, "wb");
	fwrite(code, sizeof(uint8_t), byte, fp);
	fclose(fp);
}
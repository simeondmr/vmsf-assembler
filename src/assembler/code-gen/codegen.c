#include <stdio.h>
#include "../../include/code-gen/codegen.h"

void code_gen_no_arg(uint8_t *code, enum Opcodes opcode, uint32_t *addr)
{
	code[*addr] = (opcode&0xff00)>>8;
	*addr += 1;
	code[*addr] = (opcode&0x00ff);
	*addr += 1;
}

void code_gen_one_arg(uint8_t *code, enum Opcodes opcode, uint32_t param, uint32_t *addr)
{
	code_gen_no_arg(code, opcode, addr);
	code[*addr] = (param&0xff000000)>>24;
	*addr += 1;
	code[*addr] = (param&0x00ff0000)>>16;
	*addr += 1;
	code[*addr] = (param&0x0000ff00)>>8;
	*addr += 1;
	code[*addr] = (param&0x000000ff);
	*addr += 1;
}

void code_out(const char *output_file, uint8_t *code, uint32_t byte)
{
	FILE *fp = fopen(output_file, "wb");
	fwrite(code, sizeof(uint8_t), byte, fp);
	fclose(fp);
}
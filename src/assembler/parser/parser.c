#include <stdio.h>
#include <stdlib.h>
#include "../../include/parser/parser.h"
#include "../../include/lexer/lexer.h"
#include "../../include/symbol-table/symbol_table.h"
#include "../../include/code-gen/codegen.h"

static struct Token current;

static FILE *fp;

istrs *assembly[] = {
	nop,
	push,
	add,
	sub,
	mul,
	division,
	addc,
	subc,
	inc,
	dec,
	swap,
	xor,
	and,
	or,
	not,
	call,
	push_pc,
	jmp,
	ret,
	ref,
	dup,
	mod,
	cmp,
	jmpeq,
	jmplt,
	jmpgt,
	jmple,
	jmpge,
	jmpab,
	jmpbl,
	jmpae,
	jmpbe,
	jmpne,
	divmod,
	addsp,
	subsp,
	incsp,
	decsp,
	unref,
	pushbp,
	popbp,
	pushall,
	popall,
	halt,
	pushflags,
	popflags,
	refbp,
	unrefbp,
	interrupt,
	out,
	in,
	pushhwflags,
	label
};

void init_parser(char *file)
{
	fp = fopen(file, "r");
	if (fp == NULL) {
		fprintf(stderr, "unable to open file %s\n", file);
		exit(1);
	}
}

static void match(enum Tag tag)
{
	if (current.type == tag)
		current = next_tok(fp);
	else {
		fprintf(stderr, "error");
		exit(1);
	}
}

static bool is_istr(enum Tag type)
{
	return type != FUNC && type != LITERAL && type != END_FILE;
}

void start(void)
{
	struct Function *funcs = NULL;
	uint32_t curr_byte = 0;
	uint8_t *generated_code = malloc(sizeof(uint8_t) * 3000);
	current = next_tok(fp);
	functions(&funcs, &curr_byte, generated_code);
	match(END_FILE);
	print_func_debug(funcs);
	check_resolved_func(funcs);
	//TODO: check for unresolved label
	code_out("test", generated_code, curr_byte);
	printf("Byte %d\n", curr_byte);
	free_func(funcs);
	free(generated_code);
}

static void functions(struct Function **functions, uint32_t *curr_byte, uint8_t *code)
{
	while (current.type == FUNC)
		function(functions, curr_byte, code);
}

static void function(struct Function **functions, uint32_t *curr_byte, uint8_t *code)
{
	match(FUNC);
	struct Function *curr = resolve_func(functions, current.name, *curr_byte);
	match(LABEL);
	instructions(curr, functions, curr_byte, code);
}

static void instructions(struct Function *curr, struct Function **functions, uint32_t *curr_byte, uint8_t *code)
{
	while (is_istr(current.type))
		assembly[current.type](curr, functions, curr_byte, code);
}


static void nop(struct Function *curr, struct Function **functions, uint32_t *curr_byte, uint8_t *code)
{
	match(NOP);
	code_gen_no_arg(code, OPC_NOP, curr_byte);
}

static void push(struct Function *curr, struct Function **functions, uint32_t *curr_byte, uint8_t *code)
{
	match(PUSH);
}

static void add(struct Function *curr, struct Function **functions, uint32_t *curr_byte, uint8_t *code)
{
	match(ADD);
	code_gen_no_arg(code, OPC_ADD, curr_byte);
}

static void sub(struct Function *curr, struct Function **functions, uint32_t *curr_byte, uint8_t *code)
{
	match(SUB);
	code_gen_no_arg(code, OPC_SUB, curr_byte);
}

static void mul(struct Function *curr, struct Function **functions, uint32_t *curr_byte, uint8_t *code)
{
	match(MUL);
	code_gen_no_arg(code, OPC_MUL, curr_byte);
}

static void division(struct Function *curr, struct Function **functions, uint32_t *curr_byte, uint8_t *code)
{
	match(DIV);
	code_gen_no_arg(code, OPC_DIV, curr_byte);
}

static void addc(struct Function *curr, struct Function **functions, uint32_t *curr_byte, uint8_t *code)
{
	match(ADDC);
	code_gen_no_arg(code, OPC_ADDC, curr_byte);
}

static void subc(struct Function *curr, struct Function **functions, uint32_t *curr_byte, uint8_t *code)
{
	match(SUBC);
	code_gen_no_arg(code, OPC_SUBC, curr_byte);
}

static void inc(struct Function *curr, struct Function **functions, uint32_t *curr_byte, uint8_t *code)
{
	match(INC);
	code_gen_no_arg(code, OPC_INC, curr_byte);
}

static void dec(struct Function *curr, struct Function **functions, uint32_t *curr_byte, uint8_t *code)
{
	match(DEC);
	code_gen_no_arg(code, OPC_DEC, curr_byte);
}

static void swap(struct Function *curr, struct Function **functions, uint32_t *curr_byte, uint8_t *code)
{
	match(SWAP);
	code_gen_no_arg(code, OPC_SWAP, curr_byte);
}

static void xor(struct Function *curr, struct Function **functions, uint32_t *curr_byte, uint8_t *code)
{
	match(XOR);
	code_gen_no_arg(code, OPC_XOR, curr_byte);
}

static void and(struct Function *curr, struct Function **functions, uint32_t *curr_byte, uint8_t *code)
{
	match(AND);
	code_gen_no_arg(code, OPC_AND, curr_byte);
}

static void or(struct Function *curr, struct Function **functions, uint32_t *curr_byte, uint8_t *code)
{
	match(OR);
	code_gen_no_arg(code, OPC_OR, curr_byte);
}

static void not(struct Function *curr, struct Function **functions, uint32_t *curr_byte, uint8_t *code)
{
	match(NOT);
	code_gen_no_arg(code, OPC_NOT, curr_byte);
}

static void call(struct Function *curr, struct Function **functions, uint32_t *curr_byte, uint8_t *code)
{
	match(CALL);
	isfunc_defined(functions, current.name);
	match(LITERAL);
}

static void push_pc(struct Function *curr, struct Function **functions, uint32_t *curr_byte, uint8_t *code)
{
	match(PUSHPC);
	code_gen_no_arg(code, OPC_PUSHPC, curr_byte);
}

static void jmp(struct Function *curr, struct Function **functions, uint32_t *curr_byte, uint8_t *code)
{
	match(JMP);
	islabel_defined(curr, current.name);
	match(LITERAL);
}

static void ret(struct Function *curr, struct Function **functions, uint32_t *curr_byte, uint8_t *code)
{
	match(RET);
	code_gen_no_arg(code, OPC_RET, curr_byte);
}

static void ref(struct Function *curr, struct Function **functions, uint32_t *curr_byte, uint8_t *code)
{
	match(REF);
	code_gen_no_arg(code, OPC_REF, curr_byte);
}

static void dup(struct Function *curr, struct Function **functions, uint32_t *curr_byte, uint8_t *code)
{
	match(DUP);
	code_gen_no_arg(code, OPC_DUP, curr_byte);
}

static void mod(struct Function *curr, struct Function **functions, uint32_t *curr_byte, uint8_t *code)
{
	match(MOD);
	code_gen_no_arg(code, OPC_MOD, curr_byte);
}

static void cmp(struct Function *curr, struct Function **functions, uint32_t *curr_byte, uint8_t *code)
{
	match(CMP);
	code_gen_no_arg(code, OPC_CMP, curr_byte);
}

static void jmpeq(struct Function *curr, struct Function **functions, uint32_t *curr_byte, uint8_t *code)
{
	match(JMPEQ);
	islabel_defined(curr, current.name);
	match(LITERAL);
}

static void jmplt(struct Function *curr, struct Function **functions, uint32_t *curr_byte, uint8_t *code)
{
	match(JMPLT);
	islabel_defined(curr, current.name);
	match(LITERAL);
}

static void jmpgt(struct Function *curr, struct Function **functions, uint32_t *curr_byte, uint8_t *code)
{
	match(JMPGT);
	islabel_defined(curr, current.name);
	match(LITERAL);
}

static void jmple(struct Function *curr, struct Function **functions, uint32_t *curr_byte, uint8_t *code)
{
	match(JMPLE);
	islabel_defined(curr, current.name);
	match(LITERAL);
}

static void jmpge(struct Function *curr, struct Function **functions, uint32_t *curr_byte, uint8_t *code)
{
	match(JMPGE);
	islabel_defined(curr, current.name);
	match(LITERAL);
}

static void jmpab(struct Function *curr, struct Function **functions, uint32_t *curr_byte, uint8_t *code)
{
	match(JMPAB);
	islabel_defined(curr, current.name);
	match(LITERAL);
}

static void jmpbl(struct Function *curr, struct Function **functions, uint32_t *curr_byte, uint8_t *code)
{
	match(JMPBL);
	islabel_defined(curr, current.name);
	match(LITERAL);
}

static void jmpae(struct Function *curr, struct Function **functions, uint32_t *curr_byte, uint8_t *code)
{
	match(JMPAE);
	islabel_defined(curr, current.name);
	match(LITERAL);
}

static void jmpbe(struct Function *curr, struct Function **functions, uint32_t *curr_byte, uint8_t *code)
{
	match(JMPBE);
	islabel_defined(curr, current.name);
	match(LITERAL);
}

static void jmpne(struct Function *curr, struct Function **functions, uint32_t *curr_byte, uint8_t *code)
{
	match(JMPNE);
	islabel_defined(curr, current.name);
	match(LITERAL);
}

static void divmod(struct Function *curr, struct Function **functions, uint32_t *curr_byte, uint8_t *code)
{
	match(DIVMOD);
	code_gen_no_arg(code, OPC_DIVMOD, curr_byte);
}

static void addsp(struct Function *curr, struct Function **functions, uint32_t *curr_byte, uint8_t *code)
{
	match(ADDSP);
	code_gen_no_arg(code, OPC_ADDSP, curr_byte);
}

static void subsp(struct Function *curr, struct Function **functions, uint32_t *curr_byte, uint8_t *code)
{
	match(SUBSP);
	code_gen_no_arg(code, OPC_SUBSP, curr_byte);
}

static void incsp(struct Function *curr, struct Function **functions, uint32_t *curr_byte, uint8_t *code)
{
	match(INCSP);
	code_gen_no_arg(code, OPC_INCSP, curr_byte);
}

static void decsp(struct Function *curr, struct Function **functions, uint32_t *curr_byte, uint8_t *code)
{
	match(DECSP);
	code_gen_no_arg(code, OPC_DECSP, curr_byte);
}

static void unref(struct Function *curr, struct Function **functions, uint32_t *curr_byte, uint8_t *code)
{
	match(UNREF);
	code_gen_no_arg(code, OPC_UNREF, curr_byte);
}

static void pushbp(struct Function *curr, struct Function **functions, uint32_t *curr_byte, uint8_t *code)
{
	match(PUSHBP);
	code_gen_no_arg(code, OPC_PUSHBP, curr_byte);
}

static void popbp(struct Function *curr, struct Function **functions, uint32_t *curr_byte, uint8_t *code)
{
	match(POPBP);
	code_gen_no_arg(code, OPC_POPBP, curr_byte);
}

static void pushall(struct Function *curr, struct Function **functions, uint32_t *curr_byte, uint8_t *code)
{
	match(PUSHALL);
	code_gen_no_arg(code, OPC_PUSHALL, curr_byte);
}

static void popall(struct Function *curr, struct Function **functions, uint32_t *curr_byte, uint8_t *code)
{
	match(POPALL);
	code_gen_no_arg(code, OPC_POPALL, curr_byte);
}

static void halt(struct Function *curr, struct Function **functions, uint32_t *curr_byte, uint8_t *code)
{
	match(HALT);
	code_gen_no_arg(code, OPC_HALT, curr_byte);
}

static void pushflags(struct Function *curr, struct Function **functions, uint32_t *curr_byte, uint8_t *code)
{
	match(PUSHFLAGS);
	code_gen_no_arg(code, OPC_PUSHFLAGS, curr_byte);
}

static void popflags(struct Function *curr, struct Function **functions, uint32_t *curr_byte, uint8_t *code)
{
	match(POPFLAGS);
	code_gen_no_arg(code, OPC_POPFLAGS, curr_byte);
}

static void refbp(struct Function *curr, struct Function **functions, uint32_t *curr_byte, uint8_t *code)
{
	match(REFBP);
	code_gen_no_arg(code, OPC_REFBP, curr_byte);
}

static void unrefbp(struct Function *curr, struct Function **functions, uint32_t *curr_byte, uint8_t *code)
{
	match(UNREFBP);
	code_gen_no_arg(code, OPC_UNREFBP, curr_byte);
}

static void interrupt(struct Function *curr, struct Function **functions, uint32_t *curr_byte, uint8_t *code)
{
	match(INTERRUPT);
	code_gen_no_arg(code, OPC_INT, curr_byte);
}

static void out(struct Function *curr, struct Function **functions, uint32_t *curr_byte, uint8_t *code)
{
	match(OUT);
	code_gen_no_arg(code, OPC_OUT, curr_byte);
}

static void in(struct Function *curr, struct Function **functions, uint32_t *curr_byte, uint8_t *code)
{
	match(IN);
	code_gen_no_arg(code, OPC_IN, curr_byte);
}

static void pushhwflags(struct Function *curr, struct Function **functions, uint32_t *curr_byte, uint8_t *code)
{
	match(PUSHHWFLAGS);
	code_gen_no_arg(code, OPC_PUSHFLAGS, curr_byte);
}

static void label(struct Function *curr, struct Function **functions, uint32_t *curr_byte, uint8_t *code)
{
	resolve_label(curr, current.name, *curr_byte);
	match(LABEL);
}
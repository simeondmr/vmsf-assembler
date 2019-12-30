#include <stdio.h>
#include <stdlib.h>
#include "../../include/parser/parser.h"
#include "../../include/lexer/lexer.h"
#include "../../include/symbol-table/symbol_table.h"

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
	current = next_tok(fp);
	functions(&funcs);
	match(END_FILE);
	print_func_debug(funcs);
	check_resolved_func(funcs);
	//TODO: check for unresolved label
	free_func(funcs);
}

static void functions(struct Function **functions)
{
	while (current.type == FUNC)
		function(functions);
}

static void function(struct Function **functions)
{
	match(FUNC);
	struct Function *curr = resolve_func(functions, current.name, 0); //TODO: put the correct addr
	match(LABEL);
	instructions(curr, functions);
}

static void instructions(struct Function *curr, struct Function **functions)
{
	while (is_istr(current.type))
		assembly[current.type](curr, functions);
}


static void nop(struct Function *curr, struct Function **functions)
{
	match(NOP);
}

static void push(struct Function *curr, struct Function **functions)
{
	match(PUSH);
}

static void add(struct Function *curr, struct Function **functions)
{
	match(ADD);
}

static void sub(struct Function *curr, struct Function **functions)
{
	match(SUB);
}

static void mul(struct Function *curr, struct Function **functions)
{
	match(MUL);
}

static void division(struct Function *curr, struct Function **functions)
{
	match(DIV);
}

static void addc(struct Function *curr, struct Function **functions)
{
	match(ADDC);
}

static void subc(struct Function *curr, struct Function **functions)
{
	match(SUBC);
}

static void inc(struct Function *curr, struct Function **functions)
{
	match(INC);
}

static void dec(struct Function *curr, struct Function **functions)
{
	match(DEC);
}

static void swap(struct Function *curr, struct Function **functions)
{
	match(SWAP);
}

static void xor(struct Function *curr, struct Function **functions)
{
	match(XOR);
}

static void and(struct Function *curr, struct Function **functions)
{
	match(AND);
}

static void or(struct Function *curr, struct Function **functions)
{
	match(OR);
}

static void not(struct Function *curr, struct Function **functions)
{
	match(NOT);
}

static void call(struct Function *curr, struct Function **functions)
{
	match(CALL);
	isfunc_defined(functions, current.name);
	match(LITERAL);
}

static void push_pc(struct Function *curr, struct Function **functions)
{
	match(PUSHPC);
}

static void jmp(struct Function *curr, struct Function **functions)
{
	match(JMP);
	islabel_defined(curr, current.name);
	match(LITERAL);
}

static void ret(struct Function *curr, struct Function **functions)
{
	match(RET);
}

static void ref(struct Function *curr, struct Function **functions)
{
	match(REF);
}

static void dup(struct Function *curr, struct Function **functions)
{
	match(DUP);
}

static void mod(struct Function *curr, struct Function **functions)
{
	match(MOD);
}

static void cmp(struct Function *curr, struct Function **functions)
{
	match(CMP);
}

static void jmpeq(struct Function *curr, struct Function **functions)
{
	match(JMPEQ);
	islabel_defined(curr, current.name);
	match(LITERAL);
}

static void jmplt(struct Function *curr, struct Function **functions)
{
	match(JMPLT);
	islabel_defined(curr, current.name);
	match(LITERAL);
}

static void jmpgt(struct Function *curr, struct Function **functions)
{
	match(JMPGT);
	islabel_defined(curr, current.name);
	match(LITERAL);
}

static void jmple(struct Function *curr, struct Function **functions)
{
	match(JMPLE);
	islabel_defined(curr, current.name);
	match(LITERAL);
}

static void jmpge(struct Function *curr, struct Function **functions)
{
	match(JMPGE);
	islabel_defined(curr, current.name);
	match(LITERAL);
}

static void jmpab(struct Function *curr, struct Function **functions)
{
	match(JMPAB);
	islabel_defined(curr, current.name);
	match(LITERAL);
}

static void jmpbl(struct Function *curr, struct Function **functions)
{
	match(JMPBL);
	islabel_defined(curr, current.name);
	match(LITERAL);
}

static void jmpae(struct Function *curr, struct Function **functions)
{
	match(JMPAE);
	islabel_defined(curr, current.name);
	match(LITERAL);
}

static void jmpbe(struct Function *curr, struct Function **functions)
{
	match(JMPBE);
	islabel_defined(curr, current.name);
	match(LITERAL);
}

static void jmpne(struct Function *curr, struct Function **functions)
{
	match(JMPNE);
	islabel_defined(curr, current.name);
	match(LITERAL);
}

static void divmod(struct Function *curr, struct Function **functions)
{
	match(DIVMOD);
}

static void addsp(struct Function *curr, struct Function **functions)
{
	match(ADDSP);
}

static void subsp(struct Function *curr, struct Function **functions)
{
	match(SUBSP);
}

static void incsp(struct Function *curr, struct Function **functions)
{
	match(INCSP);
}

static void decsp(struct Function *curr, struct Function **functions)
{
	match(DECSP);
}

static void unref(struct Function *curr, struct Function **functions)
{
	match(UNREF);
}

static void pushbp(struct Function *curr, struct Function **functions)
{
	match(PUSHBP);
}

static void popbp(struct Function *curr, struct Function **functions)
{
	match(POPBP);
}

static void pushall(struct Function *curr, struct Function **functions)
{
	match(PUSHALL);
}

static void popall(struct Function *curr, struct Function **functions)
{
	match(POPALL);
}

static void halt(struct Function *curr, struct Function **functions)
{
	match(HALT);
}

static void pushflags(struct Function *curr, struct Function **functions)
{
	match(PUSHFLAGS);
}

static void popflags(struct Function *curr, struct Function **functions)
{
	match(POPFLAGS);
}

static void refbp(struct Function *curr, struct Function **functions)
{
	match(REFBP);
}

static void unrefbp(struct Function *curr, struct Function **functions)
{
	match(UNREFBP);
}

static void interrupt(struct Function *curr, struct Function **functions)
{
	match(INTERRUPT);
}

static void out(struct Function *curr, struct Function **functions)
{
	match(OUT);
}

static void in(struct Function *curr, struct Function **functions)
{
	match(IN);
}

static void pushhwflags(struct Function *curr, struct Function **functions)
{
	match(PUSHHWFLAGS);
}

static void label(struct Function *curr, struct Function **functions)
{
	resolve_label(curr, current.name, 0);//TODO: put the correct addr
	match(LABEL);
}
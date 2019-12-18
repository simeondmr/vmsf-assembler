#include <stdio.h>
#include <stdlib.h>
#include "../../include/parser/parser.h"
#include "../../include/lexer/lexer.h"

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
	return type != FUNC && type != STRING && type != END_FILE;
}

void start(void)
{
	current = next_tok(fp);
	functions();
	match(END_FILE);
}

static void functions(void)
{
	while (current.type == FUNC)
		function();
}

static void function(void)
{
	match(FUNC);
	match(LABEL);
	instructions();
}

static void instructions()
{
	while (is_istr(current.type))
		assembly[current.type]();
}


static void nop(void)
{
	match(NOP);
}

static void push()
{
	match(PUSH);
}

static void add()
{
	match(ADD);
}

static void sub(void)
{
	match(SUB);
}

static void mul(void)
{
	match(MUL);
}

static void division(void)
{
	match(DIV);
}

static void addc(void)
{
	match(ADDC);
}

static void subc(void)
{
	match(SUBC);
}

static void inc(void)
{
	match(INC);
}

static void dec(void)
{
	match(DEC);
}

static void swap(void)
{
	match(SWAP);
}

static void xor(void)
{
	match(XOR);
}

static void and(void)
{
	match(AND);
}

static void or(void)
{
	match(OR);
}

static void not(void)
{
	match(NOT);
}

static void call(void)
{
	match(CALL);
}

static void push_pc(void)
{
	match(PUSHPC);
}

static void jmp(void)
{
	match(JMP);
}

static void ret(void)
{
	match(RET);
}

static void ref(void)
{
	match(REF);
}

static void dup(void)
{
	match(DUP);
}

static void mod(void)
{
	match(MOD);
}

static void cmp(void)
{
	match(CMP);
}

static void jmpeq(void)
{
	match(JMPEQ);
}

static void jmplt(void)
{
	match(JMPLT);
}

static void jmpgt(void)
{
	match(JMPGT);
}

static void jmple(void)
{
	match(JMPLE);
}

static void jmpge(void)
{
	match(JMPGE);
}

static void jmpab(void)
{
	match(JMPAB);
}

static void jmpbl(void)
{
	match(JMPBL);
}

static void jmpae(void)
{
	match(JMPAE);
}

static void jmpbe(void)
{
	match(JMPBE);
}

static void jmpne(void)
{
	match(JMPNE);
}

static void divmod(void)
{
	match(DIVMOD);
}

static void addsp(void)
{
	match(ADDSP);
}

static void subsp(void)
{
	match(SUBSP);
}

static void incsp(void)
{
	match(INCSP);
}

static void decsp(void)
{
	match(DECSP);
}

static void unref(void)
{
	match(UNREF);
}

static void pushbp(void)
{
	match(PUSHBP);
}

static void popbp(void)
{
	match(POPBP);
}

static void pushall(void)
{
	match(PUSHALL);
}

static void popall(void)
{
	match(POPALL);
}

static void halt(void)
{
	match(HALT);
}

static void pushflags(void)
{
	match(PUSHFLAGS);
}

static void popflags(void)
{
	match(POPFLAGS);
}

static void refbp(void)
{
	match(REFBP);
}

static void unrefbp(void)
{
	match(UNREFBP);
}

static void interrupt(void)
{
	match(INTERRUPT);
}

static void out(void)
{
	match(OUT);
}

static void in(void)
{
	match(IN);
}

static void pushhwflags(void)
{
	match(PUSHHWFLAGS);
}

static void label(void)
{
	match(LABEL);
}
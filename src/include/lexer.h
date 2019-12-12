#ifndef __LEXER_H
#define __LEXER_H
#include <stdbool.h>
#define NUM_WORDS 54

enum tag {
	NOP,
	PUSH,
	ADD,
	SUB,
	MUL,
	DIV,
	ADDC,
	SUBC,
	INC,
	DEC,
	SWAP,
	XOR,
	AND,
	OR,
	NOT,
	CALL,
	PUSHPC,
	JMP,
	RET,
	REF,
	DUP,
	MOD,
	CMP,
	JMPEQ,
	JMPLT,
	JMPGT,
	JMPLE,
	JMPGE,
	JMPAB,
	JMPBL,
	JMPAE,
	JMPBE,
	JMPNE,
	DIVMOD,
	ADDSP,
	SUBSP,
	INCSP,
	DECSP,
	UNREF,
	PUSHBP,
	POPBP,
	PUSHALL,
	POPALL,
	HALT,
	PUSHFLAGS,
	POPFLAGS,
	REFBP,
	UNREFBP,
	INTERRUPT,
	OUT,
	IN,
	PUSHHWFLAGS,
	FUNC,
	LABEL,
	NUMBER,
	STRING,
	END_FILE
};

struct token {
	char name[20];
	int value;
	enum tag type;
};

struct token next_tok(FILE *fp);
static bool islabel(char *lexeme);
static struct token new_tok(char *name, int value, enum tag type);
static struct token find_tok(char *token);
static struct token read_num(FILE * fp, char *c);
static char skip_space(FILE *fp);
static struct token read_kw_l(FILE *fp, char *c);

#endif
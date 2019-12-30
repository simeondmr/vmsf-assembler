#ifndef __LEXER_H
#define __LEXER_H
#include <stdbool.h>
#define NUM_WORDS 53

enum Tag {
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
	LABEL,
	FUNC,
	NUMBER,
	LITERAL,
	END_FILE
};

struct Token {
	char name[20];
	int value;
	enum Tag type;
};

struct Token next_tok(FILE *fp);
void init_lexer(void);
static bool islabel(char *lexeme);
static struct Token new_tok(char *name, int value, enum Tag type);
static struct Token find_tok(char *token);
static struct Token read_num(FILE *fp);
static void skip_space(FILE *fp);
static struct Token read_kw_l(FILE *fp);

#endif
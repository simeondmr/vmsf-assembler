#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include "../../include/lexer.h"

struct token words[] = {
	{"nop", 0, NOP},
	{"push", 0, PUSH},
	{"add", 0, ADD},
	{"sub", 0, SUB},
	{"mul", 0, MUL},
	{"div", 0, DIV},
	{"addc", 0, ADDC},
	{"subc", 0, SUBC},
	{"inc", 0, INC},
	{"dec", 0, DEC},
	{"swap", 0, SWAP},
	{"xor", 0, XOR},
	{"and", 0, AND},
	{"or", 0, OR},
	{"not", 0, NOT},
	{"call", 0, CALL},
	{"pushpc", 0, PUSHPC},
	{"jmp", 0, JMP},
	{"ret", 0, RET},
	{"ref", 0, REF},
	{"dup", 0, DUP},
	{"mod", 0, MOD},
	{"cmp", 0, CMP},
	{"jmpeq", 0, JMPEQ},
	{"jmplt", 0, JMPLT},
	{"jmpgt", 0, JMPGT},
	{"jmple", 0, JMPLE},
	{"jmpge", 0, JMPGE},
	{"jmpab", 0, JMPAB},
	{"jmpbl", 0, JMPBL},
	{"jmpae", 0, JMPAE},
	{"jmpbe", 0, JMPBE},
	{"jmpne", 0, JMPNE},
	{"divmod", 0, DIVMOD},
	{"addsp", 0, ADDSP},
	{"subsp", 0, SUBSP},
	{"incsp", 0, INCSP},
	{"decsp", 0, DECSP},
	{"unref", 0, UNREF},
	{"pushbp", 0, PUSHBP},
	{"popbp", 0, POPBP},
	{"pushall", 0, PUSHALL},
	{"popall", 0, POPALL},
	{"halt", 0, HALT},
	{"pushflags", 0, PUSHFLAGS},
	{"popflags", 0, POPFLAGS},
	{"refbp", 0, REFBP},
	{"unrefbp", 0, UNREFBP},
	{"int", 0, INTERRUPT},
	{"out", 0, OUT},
	{"in", 0, IN},
	{"pushhwflags", 0, PUSHHWFLAGS},
	{"_func", 0, FUNC}
};

static struct token find_tok(char *token) 
{
	if (islabel(token))
		return new_tok(token, 0, LABEL);
	for (int i = 0; i < NUM_WORDS; i++) 
		if (!strcmp(words[i].name, token)) {puts("find");
			return words[i];}
	return new_tok(token, 0, STRING);
}

static struct token new_tok(char *name, int value, enum tag type) 
{
	struct token tok;
	if (name != NULL)
		strcpy(tok.name, name);
	tok.value = value;
	tok.type = type;
	return tok;
}

static bool islabel(char *lexeme) 
{
	if (lexeme[strlen(lexeme) -1 ] == ':')
		return true;
	return false;
}

static char skip_space(FILE *fp)
{
	char c;
	while (fscanf(fp, "%c", &c) != EOF && (c == ' ' || c == '\n')) {
		if (c == '\n') {
			//line++
		} 
	}
	return c;
}

static struct token read_num(FILE *fp, char *c) 
{
	char number[10];
	memset(number,'\0', sizeof(number));
	strcat(number, c);
	while (fscanf(fp, "%c", &c[0]) != EOF && isdigit(c[0]))
		strcat(number, c);
	char *end;
	return new_tok(NULL, strtol(number, &end, 10), NUMBER);
}

static struct token read_kw_l(FILE *fp, char *c)
{
	char token[10];
	memset(token,'\0', sizeof(token));
	while (fscanf(fp, "%c", &c[0]) != EOF && (isalpha(c[0]) || isdigit(c[0]) || c[0] == ':' )) {
		strcat(token, c);
	}
	return find_tok(token);
}

struct token next_tok(FILE *fp) 
{	
	if (feof(fp))
		return new_tok(NULL, 0, END_FILE);
	char c[2] = {'\0','\0'};
	c[0] = skip_space(fp);
	if (isdigit(c[0])) 
		return read_num(fp, c);
	else if (isalpha(c[0]) || c[0] == '_') 
		return read_kw_l(fp, c);
}
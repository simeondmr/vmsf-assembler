#ifndef __PARSER_H
#define __PARSER_H
#include <stdbool.h>
#include "../lexer/lexer.h"
#include "../symbol-table/symbol_table.h"

typedef void (istrs)(struct Function *curr, struct Function **functions);
void init_parser(char *file);
static void match(enum Tag type);
void start(void);
static void functions(struct Function **functions);
static void function(struct Function **functions);
static void instructions(struct Function *curr, struct Function **functions);
static void nop(struct Function *curr, struct Function **functions);
static void push(struct Function *curr, struct Function **functions);
static void add(struct Function *curr, struct Function **functions);
static void sub(struct Function *curr, struct Function **functions);
static void mul(struct Function *curr, struct Function **functions);
static void division(struct Function *curr, struct Function **functions);
static void addc(struct Function *curr, struct Function **functions);
static void subc(struct Function *curr, struct Function **functions);
static void inc(struct Function *curr, struct Function **functions);
static void dec(struct Function *curr, struct Function **functions);
static void swap(struct Function *curr, struct Function **functions);
static void xor(struct Function *curr, struct Function **functions);
static void and(struct Function *curr, struct Function **functions);
static void or(struct Function *curr, struct Function **functions);
static void not(struct Function *curr, struct Function **functions);
static void call(struct Function *curr, struct Function **functions);
static void push_pc(struct Function *curr, struct Function **functions);
static void jmp(struct Function *curr, struct Function **functions);
static void ret(struct Function *curr, struct Function **functions);
static void ref(struct Function *curr, struct Function **functions);
static void dup(struct Function *curr, struct Function **functions);
static void mod(struct Function *curr, struct Function **functions);
static void cmp(struct Function *curr, struct Function **functions);
static void jmpeq(struct Function *curr, struct Function **functions);
static void jmplt(struct Function *curr, struct Function **functions);
static void jmpgt(struct Function *curr, struct Function **functions);
static void jmple(struct Function *curr, struct Function **functions);
static void jmpge(struct Function *curr, struct Function **functions);
static void jmpab(struct Function *curr, struct Function **functions);
static void jmpbl(struct Function *curr, struct Function **functions);
static void jmpae(struct Function *curr, struct Function **functions);
static void jmpbe(struct Function *curr, struct Function **functions);
static void jmpne(struct Function *curr, struct Function **functions);
static void divmod(struct Function *curr, struct Function **functions);
static void addsp(struct Function *curr, struct Function **functions);
static void subsp(struct Function *curr, struct Function **functions);
static void incsp(struct Function *curr, struct Function **functions);
static void decsp(struct Function *curr, struct Function **functions);
static void unref(struct Function *curr, struct Function **functions);
static void pushbp(struct Function *curr, struct Function **functions);
static void popbp(struct Function *curr, struct Function **functions);
static void pushall(struct Function *curr, struct Function **functions);
static void popall(struct Function *curr, struct Function **functions);
static void halt(struct Function *curr, struct Function **functions);
static void pushflags(struct Function *curr, struct Function **functions);
static void popflags(struct Function *curr, struct Function **functions);
static void refbp(struct Function *curr, struct Function **functions);
static void unrefbp(struct Function *curr, struct Function **functions);
static void interrupt(struct Function *curr, struct Function **functions);
static void out(struct Function *curr, struct Function **functions);
static void in(struct Function *curr, struct Function **functions);
static void pushhwflags(struct Function *curr, struct Function **functions);
static void label(struct Function *curr, struct Function **functions);
static bool is_istr(enum Tag type);
static void error(char *s);
#endif

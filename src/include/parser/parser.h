#ifndef __PARSER_H
#define __PARSER_H
#include <stdbool.h>
#include "../lexer/lexer.h"

typedef void (istrs)(void);
void init_parser(char *file);
static void match(enum Tag type);
void start(void);
static void functions(void);
static void function(void);
static void instructions(void);
static void instruction(void);
static void nop(void);
static void push(void);
static void add(void);
static void sub(void);
static void mul(void);
static void division(void);
static void addc(void);
static void subc(void);
static void inc(void);
static void dec(void);
static void swap(void);
static void xor(void);
static void and(void);
static void or(void);
static void not(void);
static void call(void);
static void push_pc(void);
static void jmp(void);
static void ret(void);
static void ref(void);
static void dup(void);
static void mod(void);
static void cmp(void);
static void jmpeq(void);
static void jmplt(void);
static void jmpgt(void);
static void jmple(void);
static void jmpge(void);
static void jmpab(void);
static void jmpbl(void);
static void jmpae(void);
static void jmpbe(void);
static void jmpne(void);
static void divmod(void);
static void addsp(void);
static void subsp(void);
static void incsp(void);
static void decsp(void);
static void unref(void);
static void pushbp(void);
static void popbp(void);
static void pushall(void);
static void popall(void);
static void halt(void);
static void pushflags(void);
static void popflags(void);
static void refbp(void);
static void unrefbp(void);
static void interrupt(void);
static void out(void);
static void in(void);
static void pushhwflags(void);
static void label(void);
static bool is_istr(enum Tag type);
#endif
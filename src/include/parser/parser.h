#ifndef __PARSER_H
#define __PARSER_H
#include <stdint.h>
#include <stdbool.h>
#include "../lexer/lexer.h"
#include "../symbol-table/symbol_table.h"

typedef void (istrs)(struct Function *curr, struct Function **functions, uint32_t *curr_byte, uint8_t *code);
void init_parser(char *file);
static void match(enum Tag type);
void start(void);
static void functions(struct Function **functions, uint32_t *curr_byte, uint8_t *code);
static void function(struct Function **functions, uint32_t *curr_byte, uint8_t *code);
static void instructions(struct Function *curr, struct Function **functions, uint32_t *curr_byte, uint8_t *code);
static void nop(struct Function *curr, struct Function **functions, uint32_t *curr_byte, uint8_t *code);
static void push(struct Function *curr, struct Function **functions, uint32_t *curr_byte, uint8_t *code);
static void add(struct Function *curr, struct Function **functions, uint32_t *curr_byte, uint8_t *code);
static void sub(struct Function *curr, struct Function **functions, uint32_t *curr_byte, uint8_t *code);
static void mul(struct Function *curr, struct Function **functions, uint32_t *curr_byte, uint8_t *code);
static void division(struct Function *curr, struct Function **functions, uint32_t *curr_byte, uint8_t *code);
static void addc(struct Function *curr, struct Function **functions, uint32_t *curr_byte, uint8_t *code);
static void subc(struct Function *curr, struct Function **function, uint32_t *curr_byte, uint8_t *code);
static void inc(struct Function *curr, struct Function **functions, uint32_t *curr_byte, uint8_t *code);
static void dec(struct Function *curr, struct Function **functions, uint32_t *curr_byte, uint8_t *code);
static void swap(struct Function *curr, struct Function **functions, uint32_t *curr_byte, uint8_t *code);
static void xor(struct Function *curr, struct Function **functions, uint32_t *curr_byte, uint8_t *code);
static void and(struct Function *curr, struct Function **functions, uint32_t *curr_byte, uint8_t *code);
static void or(struct Function *curr, struct Function **functions, uint32_t *curr_byte, uint8_t *code);
static void not(struct Function *curr, struct Function **functions, uint32_t *curr_byte, uint8_t *code);
static void call(struct Function *curr, struct Function **functions, uint32_t *curr_byte, uint8_t *code);
static void push_pc(struct Function *curr, struct Function **functions, uint32_t *curr_byte, uint8_t *code);
static void jmp(struct Function *curr, struct Function **functions, uint32_t *curr_byte, uint8_t *code);
static void ret(struct Function *curr, struct Function **functions, uint32_t *curr_byte, uint8_t *code);
static void ref(struct Function *curr, struct Function **functions, uint32_t *curr_byte, uint8_t *code);
static void dup(struct Function *curr, struct Function **functions, uint32_t *curr_byte, uint8_t *code);
static void mod(struct Function *curr, struct Function **functions, uint32_t *curr_byte, uint8_t *code);
static void cmp(struct Function *curr, struct Function **functions, uint32_t *curr_byte, uint8_t *code);
static void jmpeq(struct Function *curr, struct Function **functions, uint32_t *curr_byte, uint8_t *code);
static void jmplt(struct Function *curr, struct Function **functions, uint32_t *curr_byte, uint8_t *code);
static void jmpgt(struct Function *curr, struct Function **functions, uint32_t *curr_byte, uint8_t *code);
static void jmple(struct Function *curr, struct Function **functions, uint32_t *curr_byte, uint8_t *code);
static void jmpge(struct Function *curr, struct Function **functions, uint32_t *curr_byte, uint8_t *code);
static void jmpab(struct Function *curr, struct Function **functions, uint32_t *curr_byte, uint8_t *code);
static void jmpbl(struct Function *curr, struct Function **functions, uint32_t *curr_byte, uint8_t *code);
static void jmpae(struct Function *curr, struct Function **functions, uint32_t *curr_byte, uint8_t *code);
static void jmpbe(struct Function *curr, struct Function **functions, uint32_t *curr_byte, uint8_t *code);
static void jmpne(struct Function *curr, struct Function **functions, uint32_t *curr_byte, uint8_t *code);
static void divmod(struct Function *curr, struct Function **functions, uint32_t *curr_byte, uint8_t *code);
static void addsp(struct Function *curr, struct Function **functions, uint32_t *curr_byte, uint8_t *code);
static void subsp(struct Function *curr, struct Function **functions, uint32_t *curr_byte, uint8_t *code);
static void incsp(struct Function *curr, struct Function **functions, uint32_t *curr_byte, uint8_t *code);
static void decsp(struct Function *curr, struct Function **functions, uint32_t *curr_byte, uint8_t *code);
static void unref(struct Function *curr, struct Function **functions, uint32_t *curr_byte, uint8_t *code);
static void pushbp(struct Function *curr, struct Function **functions, uint32_t *curr_byte, uint8_t *code);
static void popbp(struct Function *curr, struct Function **functions, uint32_t *curr_byte, uint8_t *code);
static void pushall(struct Function *curr, struct Function **functions, uint32_t *curr_byte, uint8_t *code);
static void popall(struct Function *curr, struct Function **functions, uint32_t *curr_byte, uint8_t *code);
static void halt(struct Function *curr, struct Function **functions, uint32_t *curr_byte, uint8_t *code);
static void pushflags(struct Function *curr, struct Function **functions, uint32_t *curr_byte, uint8_t *code);
static void popflags(struct Function *curr, struct Function **functions, uint32_t *curr_byte, uint8_t *code);
static void refbp(struct Function *curr, struct Function **functions, uint32_t *curr_byte, uint8_t *code);
static void unrefbp(struct Function *curr, struct Function **functions, uint32_t *curr_byte, uint8_t *code);
static void interrupt(struct Function *curr, struct Function **functions, uint32_t *curr_byte, uint8_t *code);
static void out(struct Function *curr, struct Function **functions, uint32_t *curr_byte, uint8_t *code);
static void in(struct Function *curr, struct Function **function, uint32_t *curr_byte, uint8_t *code);
static void pushhwflags(struct Function *curr, struct Function **functions, uint32_t *curr_byte, uint8_t *code);
static void label(struct Function *curr, struct Function **functions, uint32_t *curr_byte, uint8_t *code);
static bool is_istr(enum Tag type);
static void error(char *s);
#endif

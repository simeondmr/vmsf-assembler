#ifndef __SYMBOL_H
#define __SYMBOL_H
#include <stdint.h>
#include <stdbool.h>

struct Label {
	char *name;
	uint32_t addr;
	bool resolved;
	struct Label *next;
};

struct Function {
	char *name;
	uint32_t addr;
	bool resolved;
	struct Label *labels;
	struct Function *next;
};
void print_func_debug(struct Function *function);
static struct Function *new_func(char *name, uint32_t addr, bool resolved);
static struct Label *new_label(char *name, uint32_t addr, bool resolved);
static struct Function *search_func(struct Function *head, char *name);
static struct Label *search_label(struct Function *curr, char *name);
struct Function *decl_func(struct Function **head, char *name, uint32_t addr, bool resolved);
struct Function *resolve_func(struct Function **head, char *name, uint32_t addr);
void resolve_label(struct Function *head, char *name, uint32_t addr);
void isfunc_defined(struct Function **head, char *name);
void check_resolved_func(struct Function *head);
void free_func(struct Function *head);
void decl_label(struct Function *head, char *name, uint32_t addr, bool resolved);
void islabel_defined(struct Function *curr, char *name);

#endif
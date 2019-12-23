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

static struct Function *new_func(char *name, uint32_t addr, bool resolved);
static struct Label *new_label(char *name, uint32_t addr, bool resolved);
static struct Function *search_func(struct Function *head, char *name);
static struct Label *search_label(struct Function *head, char *fname, char *name);
bool decl_func(struct Function **head, char *name, uint32_t addr, bool resolved);
bool decl_label(struct Function *head, char *fname, char *name, uint32_t addr, bool resolved);
void resolve_func(struct Function *head, char *name, uint32_t addr);
void resolve_label(struct Function *head, char *fname, char *name, uint32_t addr);
void free_func(struct Function *head);

#endif
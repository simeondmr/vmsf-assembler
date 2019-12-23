#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../include/symbol-table/symbol_table.h"

static struct Function *new_func(char *name, uint32_t addr, bool resolved)
{
	struct Function *function = malloc(sizeof(struct Function));
	function->name = malloc((strlen(name) + 1) * sizeof(char));
	strcpy(function->name, name);
	function->addr = addr;
	function->resolved = resolved;
	function->next = NULL;
	function->labels = NULL;
	return function;
}

static struct Label *new_label(char *name, uint32_t addr, bool resolved)
{
	struct Label *label = malloc(sizeof(struct Label));
	label->name = malloc((strlen(name) + 1) *sizeof(char));
	strcpy(label->name, name);
	label->addr = addr;
	label->resolved = resolved;
	label->next = NULL;
	return label;
}

static struct Function *search_func(struct Function *head, char *name)
{
	while (head != NULL) {
		if (!strcmp(head->name, name))
			return head;
		head = head->next;
	}
	return NULL;
}

static struct Label *search_label(struct Function *head, char *fname, char *name)
{
	struct Function *func = search_func(head, fname);
	while (func->labels != NULL) {
		if (!strcmp(func->labels->name, name))
			return func->labels;
		func->labels = func->labels->next;
	}
	return NULL;
}

bool decl_func(struct Function **head, char *name, uint32_t addr, bool resolved)
{
	if (*head == NULL) 
		*head = new_func(name, addr, resolved);
	else {
		struct Function *curr = *head;
		while (curr->next != NULL) {
			if (!strcmp(curr->name, name))
				return false;
			curr = curr->next;
		}
		if (!strcmp(curr->name, name))
			return false;
		curr->next = new_func(name, addr, resolved);
	}
	return true;
}

bool decl_label(struct Function *head, char *fname, char *name, uint32_t addr, bool resolved)
{
	struct Function *curr = search_func(head, fname);
	if (curr->labels == NULL)
		curr->labels = new_label(name, addr, resolved);
	else {
		struct Label *labels = curr->labels;
		while (labels->next != NULL) {
			if (!strcmp(labels->name, name))
				return false;
			labels = labels->next;
		}
		if (!strcmp(labels->name, name))
			return false;
		labels->next = new_label(name, addr, resolved);
	}
	return true;
}



void resolve_func(struct Function *head, char *name, uint32_t addr)
{
	struct Function *func = search_func(head, name);
	if (func != NULL) {
		func->addr = addr;
		func->resolved = true;
	} else fprintf(stderr, "The function %s is not finded\n", name);
}

void resolve_label(struct Function *head, char *fname, char *name, uint32_t addr)
{
	struct Label *label = search_label(head, fname, name);
	if (label != NULL) {
		label->addr = addr;
		label->resolved = true;
	} else fprintf(stderr, "Label not found\n");
}

void free_func(struct Function *head)
{
	while (head != NULL) {
		struct Function *next = head->next;
		free(head->name);
		while (head->labels != NULL) {
			struct Label *next = head->labels->next;
			free(head->labels->name);
			free(head->labels);
			head->labels = next;
			
		}
		free(head);
		head = next;
	}
}

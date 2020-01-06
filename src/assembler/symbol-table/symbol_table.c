#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../include/symbol-table/symbol_table.h"

void print_func_debug(struct Function *function)
{
	while (function != NULL) {
		printf("Name: %s resolved: %d byte: %d\n", function->name, function->resolved, function->addr);
		struct Label *tmp = function->labels;
		while (tmp != NULL) {
			printf("Label %s resolved %d byte: %d\n", tmp->name, tmp->resolved, tmp->addr);
			tmp = tmp->next;
		}
		function = function->next;
	}
}

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
	label->name = malloc((strlen(name) + 1) * sizeof(char));
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

static struct Label *search_label(struct Function *curr, char *name)
{
	struct Label *tmp = curr->labels;
	while (tmp != NULL) {
		if (!strcmp(tmp->name, name))
			return tmp;
		tmp = tmp->next;
	}
	return NULL;
}

struct Function *decl_func(struct Function **head, char *name, uint32_t addr, bool resolved)
{
	if (*head == NULL) {
		*head = new_func(name, addr, resolved);
		return *head;
	} else {
		struct Function *curr = *head;
		while (curr->next != NULL) {
			if (!strcmp(curr->name, name)) {
				fprintf(stderr, "Error: function '%s' is already present\n", name);
				exit(1);
			}
			curr = curr->next;
		}
		if (!strcmp(curr->name, name)) {
			fprintf(stderr, "Error: function '%s' is already present\n", name);
			exit(1);
		}
		curr->next = new_func(name, addr, resolved);
		return curr->next;
	}
}

struct Label *decl_label(struct Function *curr, char *name, uint32_t addr, bool resolved)
{
	if (curr->labels == NULL) {
		curr->labels = new_label(name, addr, resolved);
		return curr->labels;
	} else {
		struct Label *labels = curr->labels;
		while (labels->next != NULL) {
			if (!strcmp(labels->name, name)) {
				fprintf(stderr, "Error in function '%s': label %s is already present\n", curr->name, name);
				exit(1);
			}
			labels = labels->next;
		}
		if (!strcmp(labels->name, name)) {
				fprintf(stderr, "Error in function '%s': label %s is already present\n", curr->name, name);
				exit(1);
		}
		labels->next = new_label(name, addr, resolved);
		return labels->next;
	}
}

struct Function *resolve_func(struct Function **head, char *name, uint32_t addr)
{
	struct Function *func = search_func(*head, name);
	if (func != NULL && !func->resolved) {
		func->addr = addr;
		func->resolved = true;
		return func;
	} else return decl_func(head, name, addr, true);
}

struct Label *resolve_label(struct Function *head, char *name, uint32_t addr)
{
	struct Label *label = search_label(head, name);
	if (label != NULL && !label->resolved) {
		label->addr = addr;
		label->resolved = true;
		return label;
	} else return decl_label(head, name, addr, true);
}

void check_resolved_func(struct Function *head)
{
	while (head != NULL) {
		if (!head->resolved) {
			fprintf(stderr, "Error: the function '%s' is not defined\n", head->name);
			exit(1);
		}
		head = head->next;
	}
}

void isfunc_defined(struct Function **head, char *name)
{
	struct Function *func = search_func(*head, name);
	if (func == NULL)
		decl_func(head, name, 0, false);
}

void islabel_defined(struct Function *curr, char *name)
{
	struct Label *label = search_label(curr, name);
	if (label == NULL)
		decl_label(curr, name, 0, false); 
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
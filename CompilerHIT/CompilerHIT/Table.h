#ifndef TABLE_H
#define TABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Hash.h"

FILE *semantic_report; /*file pointer for parser report*/

typedef enum elm_type
{
	REAL,
	INTEGER,
	NULL_type,
	INDEX
} elm_type;

typedef struct table_entry {
	//scope table parameters

	//variable
	char *name;
	elm_type type;
	int size;

	//function
	elm_type return_type;
	int num_of_parameters;
	ZHashTable *parameters_list;

	//settings
	int is_function;

} table_entry;

typedef struct table_ptr
{
	struct table_ptr *father;
	ZHashTable *used;
	ZHashTable *unused;
	table_entry *entry;
} table_ptr;

char *getTypeName(elm_type type);

void print_sem(char **msg, int num);

table_ptr *cur_table;

table_ptr *make_table(table_ptr *current_table, char *rule);

table_ptr *pop_table(table_ptr *current_table, char *rule);

table_entry *insert(table_ptr *current_table, char *id_name, int line);

table_entry *lookup(table_ptr *current_table, char *id_name);

table_entry *find(table_ptr *current_table, char *id_name, int line, int use);

void set_id_type(table_entry *id_entry, elm_type id_type);                                                             

elm_type get_id_type(table_entry *id_entry);

void use_id(table_ptr *current_table, char *id_name);

int is_unused(table_ptr *current_table);

void print_unused(table_ptr *current_table);

void reset_table();

#endif

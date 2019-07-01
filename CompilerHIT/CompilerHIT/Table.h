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
	NULL_type
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
	struct table_entry *parameters_list;

	//settings
	int is_function;
	int depth;

} table_entry;

typedef struct table_ptr
{
	struct table_ptr *father;
	ZHashTable *hashtable;
	table_entry *entry;
	int depth;
} table_ptr;

table_ptr *cur_table;

table_ptr *make_table(table_ptr *current_table, char *rule);

table_ptr *pop_table(table_ptr *current_table, char *rule);

table_entry *insert(table_ptr *current_table, char *id_name, int line);

table_entry *lookup(table_ptr *current_table, char *id_name);

table_entry *find(table_ptr *current_table, char *id_name, int line);

void set_id_type(table_entry *id_entry, elm_type id_type);                                                             

elm_type get_id_type(table_entry *id_entry);

void reset_table();

#endif

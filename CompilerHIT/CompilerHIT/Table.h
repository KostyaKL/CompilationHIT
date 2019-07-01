#ifndef TABLE_H
#define TABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Hash.h"

FILE *semantic_report; /*file pointer for parser report*/

typedef struct table_ptr
{
	struct table_ptr *father;
	hashtable_t *hashtable;
	table_entry *entry;
	int depth;
} table_ptr;

table_ptr *make_table(table_ptr *current_table);

table_ptr *pop_table(table_ptr *current_table);

table_entry *insert(table_ptr *current_table, char *id_name);

table_entry *lookup(table_ptr *current_table, char *id_name);

table_entry *find(table_ptr *current_table, char *id_name);                                                                

void set_id_type(table_entry *id_entry, elm_type id_type);                                                             

elm_type get_id_type(table_entry *id_entry);

void reset_table();

#endif

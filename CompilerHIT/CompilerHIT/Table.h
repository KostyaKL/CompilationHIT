#ifndef TABLE_H
#define TABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum elm_type
{
	REAL,
	INTEGER,
	NULL_type
}elm_type;

typedef struct table_entry
{
	//table entry parameters
}table_entry;

typedef struct table_ptr
{
	table_ptr *father;
	table_entry *entry;
}table_ptr;

table_ptr *make_table(table_ptr *current_table);

table_ptr *pop_table(table_ptr *current_table);

table_entry *insert(table_ptr *current_table, char *id_name);

table_entry *lookup(table_ptr *current_table, char *id_name);

table_entry *find(table_ptr *current_table, char *id_name);                                                                

void set_id_type(table_entry *id_entry, elm_type id_type);                                                             

elm_type get_id_type(table_entry *id_entry);

#endif

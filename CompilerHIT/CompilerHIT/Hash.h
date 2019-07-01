#ifndef HASH_H
#define HASH_H

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>

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

typedef struct entry_s
{
	char *key;
	table_entry *value;
	struct entry_s *next;

} entry_s;

typedef struct entry_s entry_t;

struct hashtable_s {
	int size;
	struct entry_s **table;
};

typedef struct hashtable_s hashtable_t;

/* Create a new hashtable. */
hashtable_t *ht_create(int size);

/* Hash a string for a particular hash table. */
int ht_hash(hashtable_t *hashtable, char *key);

/* Create a key-value pair. */
entry_t *ht_newpair(char *key, table_entry *value);

/* Insert a key-value pair into a hash table. */
void ht_set(hashtable_t *hashtable, char *key, table_entry *value);

/* Retrieve a key-value pair from a hash table. */
table_entry *ht_get(hashtable_t *hashtable, char *key);

#endif
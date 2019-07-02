#include "Table.h"

char *getTypeName(elm_type type) {
	switch (type) {
	case REAL: return "Real";
	case INTEGER: return "Integer";
	case NULL_type: return "Void";
	}
}

void print_sem(char **msg, int num) {
	char * new_str;
	int size = 0;

	for (int i = 0; i < num;i++) {
		size += strlen(msg[i]);
	}

	if ((new_str = malloc(size + 2)) != NULL) {
		new_str[0] = '\0';   // ensures the memory is an empty string
		for (int i = 0; i < num;i++) {
			strcat(new_str, msg[i]);
		}
		strcat(new_str, "\n");
	}
	fprintf(semantic_report, new_str);
}

table_ptr *make_table(table_ptr *current_table, char *rule) {
	table_ptr *tmp;

	if (current_table == NULL) {
		current_table = (table_ptr*)malloc(sizeof(table_ptr));
		if (current_table == NULL)
		{
			fprintf(semantic_report, "\nUnable to allocate memory! \n");
			exit(0);
		}
		current_table->father = NULL;
		current_table->hashtable = zcreate_hash_table();
		current_table->entry = NULL;

		char *msg[2] = { "new scope ", rule };
		print_sem(msg, 2);
		
		return current_table;
	}

	tmp = (table_ptr*)malloc(sizeof(table_ptr));
	if (tmp == NULL)
	{
		fprintf(semantic_report, "\nUnable to allocate memory! \n");
		exit(0);
	}
	tmp->father = current_table;
	tmp->hashtable = zcreate_hash_table();
	tmp->entry = NULL;

	char *msg[2] = { "new scope ", rule };
	print_sem(msg, 2);

	return tmp;
}

table_ptr *pop_table(table_ptr *current_table, char *rule) {
	table_ptr *tmp;

	//free(current_table->entry); //free entry data structure????
								//free hash table?
	tmp = current_table->father;
	free(current_table);

	char *msg[2] = { "end scope ", rule };
	print_sem(msg, 2);

	return tmp;
}

table_entry *insert(table_ptr *current_table, char *id_name, int line) {
	table_entry *new_entry;
	new_entry = lookup(current_table, id_name);
	if (new_entry != NULL) {
		fprintf(semantic_report, "\tERROR line %d: duplicate declaration of the same name: %s \n", line, id_name);
		return NULL;
	}
	
	new_entry = (table_entry*)malloc(sizeof(table_entry));
	if (new_entry == NULL)
	{
		fprintf(semantic_report, "\nUnable to allocate memory! \n");
		exit(0);
	}
	new_entry->is_function = 0;
	new_entry->is_used = 0;
	new_entry->name = id_name;
	new_entry->num_of_parameters = 0;
	new_entry->parameters_list = NULL;
	new_entry->return_type = NULL_type;
	new_entry->size = 1;
	new_entry->type = NULL_type;

	zhash_set(cur_table->hashtable, id_name, new_entry);

	return new_entry;
}

table_entry *lookup(table_ptr *current_table, char *id_name) {
	return zhash_get(current_table->hashtable, id_name);
}

table_entry *find(table_ptr *current_table, char *id_name, int line) {
	table_ptr *tab = current_table;
	table_entry *id_entry;
	while (tab != NULL)
	{
		id_entry = lookup(tab, id_name);
		if (id_entry != NULL)
			return (id_entry);
		else
			tab = tab->father;
	}
	fprintf(semantic_report, "\tERROR line %d: undeclared identifier: %s \n", line, id_name);
	return NULL;
}

void set_id_type(table_entry *id_entry, elm_type id_type) {
	id_entry->type = id_type;
}

elm_type get_id_type(table_entry *id_entry) {
	return id_entry->type;
}

void reset_table() {
	table_ptr *tmp;
	if(cur_table != NULL)
	while (cur_table != NULL && cur_table->father != NULL) {
		free(cur_table->entry); //free entry data structure????
								//free hash table?
		zfree_hash_table(cur_table->hashtable);

		tmp = cur_table;
		cur_table = cur_table->father;
		free(tmp);
	}
	if (cur_table != NULL) {
		free(cur_table->entry); //free entry data structure????
								//free hash table?
		zfree_hash_table(cur_table->hashtable);
	}

	cur_table = NULL;
}
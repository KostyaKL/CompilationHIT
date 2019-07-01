#include "Table.h"

table_ptr *cur_table = NULL;

table_ptr *make_table(table_ptr *current_table) {
	table_ptr *tmp;
	if (cur_table == NULL) {
		cur_table = (table_ptr*)malloc(sizeof(table_ptr));
		if (cur_table == NULL)
		{
			fprintf(semantic_report, "\nUnable to allocate memory! \n");
			exit(0);
		}
		cur_table->father = NULL;
		cur_table->hashtable = ht_create(65536);
		cur_table->entry = NULL;
		cur_table->depth = 0;
		return cur_table;
	}

	tmp = (table_ptr*)malloc(sizeof(table_ptr));
	if (tmp == NULL)
	{
		fprintf(semantic_report, "\nUnable to allocate memory! \n");
		exit(0);
	}
	tmp->father = current_table;
	memcpy(tmp->hashtable, current_table->hashtable, sizeof(current_table->hashtable));
	tmp->entry = NULL;
	tmp->depth = current_table->depth + 1;
	return tmp;
}

table_ptr *pop_table(table_ptr *current_table) {
	table_ptr *tmp;
	free(current_table->entry); //free entry data structure????
								//free hash table?
	tmp = current_table->father;
	free(current_table);
	return tmp;
}

table_entry *insert(table_ptr *current_table, char *id_name) {
	table_entry *new_entry;
	new_entry = lookup(current_table->hashtable, id_name);
	if (new_entry != NULL) {
		if (new_entry->depth == current_table->depth) {
			fprintf(semantic_report, "ERROR: duplicate declaration of the same name %s \n", id_name);
			return NULL;
		}
		else{
			new_entry->depth = current_table->depth;
			return new_entry;
		}
	}

	new_entry = (table_entry*)malloc(sizeof(table_entry));
	if (new_entry == NULL)
	{
		fprintf(semantic_report, "\nUnable to allocate memory! \n");
		exit(0);
	}
	new_entry->is_function = 0;
	new_entry->depth = current_table->depth;
	new_entry->name = id_name;
	new_entry->num_of_parameters = 0;
	new_entry->parameters_list = NULL;
	new_entry->return_type = NULL_type;
	new_entry->size = 1;
	new_entry->type = NULL_type;

	ht_set(current_table->hashtable, id_name, new_entry);

	return new_entry;
}

table_entry *lookup(table_ptr *current_table, char *id_name) {
	return ht_get(current_table->hashtable, id_name);
}

table_entry *find(table_ptr *current_table, char *id_name) {
	table_entry *srch = ht_get(current_table->hashtable, id_name);
	if (srch == NULL) {
		fprintf(semantic_report, "ERROR: undeclared identifier %s \n", id_name);
		return NULL;
	}
	return srch;
}

void set_id_type(table_entry *id_entry, elm_type id_type) {
	id_entry->type = id_type;
}

elm_type get_id_type(table_entry *id_entry) {
	return id_entry->type;
}

void reset_table() {
	table_ptr *tmp;
	while (cur_table->father != NULL) {
		free(cur_table->entry); //free entry data structure????
								//free hash table?

		tmp = cur_table;
		cur_table = cur_table->father;
		free(tmp);
	}
	free(cur_table->entry); //free entry data structure????
							//free hash table?

}
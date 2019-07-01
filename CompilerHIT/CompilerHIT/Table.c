#include "Table.h"

table_ptr *make_table(table_ptr *current_table, char *rule) {
	table_ptr *tmp;

	table_entry *tmp_entry = NULL;
	struct ZHashEntry *entry;
	size_t size, hash;

	if (cur_table == NULL) {
		cur_table = (table_ptr*)malloc(sizeof(table_ptr));
		if (cur_table == NULL)
		{
			fprintf(semantic_report, "\nUnable to allocate memory! \n");
			exit(0);
		}
		cur_table->father = NULL;
		cur_table->hashtable = zcreate_hash_table();
		zhash_set(cur_table->hashtable, "_init", NULL);
		cur_table->entry = NULL;
		cur_table->depth = 0;


		char * new_str;
		if ((new_str = malloc(strlen("new scope ") + strlen(rule) + 2)) != NULL) {
			new_str[0] = '\0';   // ensures the memory is an empty string
			strcat(new_str, "new scope ");
			strcat(new_str, rule);
			strcat(new_str, "\n");
		}
		else {
			fprintf(semantic_report, "malloc failed!\n");
			exit(0);
		}
		fprintf(semantic_report, new_str);

		return cur_table;
	}

	tmp = (table_ptr*)malloc(sizeof(table_ptr));
	if (tmp == NULL)
	{
		fprintf(semantic_report, "\nUnable to allocate memory! \n");
		exit(0);
	}
	tmp->father = cur_table;
	tmp->hashtable = zcreate_hash_table();
	zhash_set(tmp->hashtable, "_init", NULL);

	hash = zgenerate_hash(cur_table->hashtable, "_init");
	entry = cur_table->hashtable->entries[hash];
	while (entry) {
		if (entry->val != NULL && strcmp(entry->key, "_init") != 0) {
			memcpy(tmp_entry, (table_entry*)entry->val, sizeof(table_entry));

			zhash_set(tmp->hashtable, entry->key, tmp_entry);
		}
		entry = entry->next;
	}

	tmp->entry = NULL;
	tmp->depth = current_table->depth + 1;

	current_table = tmp;
	cur_table = tmp;

	char * new_str;
	if ((new_str = malloc(strlen("new scope ") + strlen(rule) + 2)) != NULL) {
		new_str[0] = '\0';   // ensures the memory is an empty string
		strcat(new_str, "new scope ");
		strcat(new_str, rule);
		strcat(new_str, "\n");
	}
	else {
		fprintf(semantic_report, "malloc failed!\n");
		exit(0);
	}
	fprintf(semantic_report, new_str);

	return tmp;
}

table_ptr *pop_table(table_ptr *current_table, char *rule) {
	table_ptr *tmp;
	
	struct ZHashEntry *entry;
	size_t size, hash;
	hash = zgenerate_hash(cur_table->hashtable, "_init");
	entry = cur_table->hashtable->entries[hash];
	while (entry) {
		if (entry->val != NULL && strcmp(entry->key, "_init") != 0) {
			fprintf(semantic_report, "\ttype: %d, id: %s, size: %d\n", ((table_entry*)entry->val)->type, ((table_entry*)entry->val)->name, ((table_entry*)entry->val)->size);
		}
		entry = entry->next;
	}


	//free(current_table->entry); //free entry data structure????
								//free hash table?
	tmp = cur_table->father;
	free(cur_table);

	char * new_str;
	if ((new_str = malloc(strlen("end scope ") + strlen(rule) + 2)) != NULL) {
		new_str[0] = '\0';   // ensures the memory is an empty string
		strcat(new_str, "end scope ");
		strcat(new_str, rule);
		strcat(new_str, "\n");
	}
	else {
		fprintf(semantic_report, "malloc failed!\n");
		exit(0);
	}
	fprintf(semantic_report, new_str);

	current_table = tmp;
	cur_table = tmp;

	return tmp;
}

table_entry *insert(table_ptr *current_table, char *id_name, int line) {
	table_entry *new_entry;
	new_entry = lookup(cur_table->hashtable, id_name);
	if (new_entry != NULL) {
		if (new_entry->depth == cur_table->depth) {
			fprintf(semantic_report, "\tERROR line %d: duplicate declaration of the same name %s \n", line, id_name);
			return NULL;
		}
		else{
			new_entry->depth = cur_table->depth;
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
	new_entry->depth = cur_table->depth;
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
	return zhash_get(cur_table->hashtable, id_name);
}

table_entry *find(table_ptr *current_table, char *id_name, int line) {
	table_entry *srch = zhash_get(cur_table->hashtable, id_name);
	if (srch == NULL) {
		fprintf(semantic_report, "\tERROR line %d: undeclared identifier %s \n", line, id_name);
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
	//cur_table = NULL;
}
#include "Table.h"

char *getTypeName(elm_type type) {
	switch (type) {
	case REAL: return "Real";
	case INTEGER: return "Integer";
	case NULL_type: return "Void";
	case INDEX: return "Index";
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
		current_table->unused = zcreate_hash_table();
		current_table->used = zcreate_hash_table();

		zhash_set(current_table->unused, "0", NULL);

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
	tmp->unused = zcreate_hash_table();
	tmp->used = zcreate_hash_table();

	zhash_set(tmp->unused, "0", NULL);

	char *msg[2] = { "new scope ", rule };
	print_sem(msg, 2);

	return tmp;
}

table_ptr *pop_table(table_ptr *current_table, char *rule) {
	table_ptr *tmp;
	int is_unused_exist = is_unused(current_table);
	if (is_unused_exist) {
		print_unused(current_table);
	}

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
	new_entry->name = id_name;
	new_entry->num_of_parameters = 0;
	new_entry->parameters_list = NULL;
	new_entry->return_type = NULL_type;
	new_entry->size = 1;
	new_entry->type = NULL_type;
	new_entry->param_num = 0;

	zhash_set(cur_table->unused, id_name, new_entry);

	return new_entry;
}

table_entry *lookup(table_ptr *current_table, char *id_name) {
	table_entry *exist = NULL;
	exist = zhash_get(current_table->unused, id_name);
	if (exist != NULL) {
		return exist;
	}
	exist = zhash_get(current_table->used, id_name);
	return exist;
}

table_entry *find(table_ptr *current_table, char *id_name, int line, int use) {
	table_ptr *tab = current_table;
	table_entry *id_entry;
	while (tab != NULL)
	{
		id_entry = lookup(tab, id_name);
		if (id_entry != NULL) {
			if (use) {
				use_id(tab, id_name);
			}
			return (id_entry);
		}
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

void use_id(table_ptr *current_table, char *id_name) {
	table_entry *tmp = NULL;
	tmp = zhash_get(current_table->unused, id_name);
	if (tmp != NULL) {
		zhash_delete(current_table->unused, id_name);
		zhash_set(cur_table->used, tmp->name, tmp);
	}
}

int is_unused(table_ptr *current_table) {
	if (current_table->unused->entry_count == 1) {
		return 0;
	}
	return 1;
}

void print_unused(table_ptr *current_table) {
	size_t hash;
	struct ZHashEntry *entry;

	hash = zgenerate_hash(current_table->unused, "0");
	entry = current_table->unused->entries[hash];

	fprintf(semantic_report, "\tthere is %d unsused idss and %d used ids\n", current_table->unused->entry_count, current_table->used->entry_count );
	/*while (entry) {
		fprintf(semantic_report, "\t\t%s\n", ((table_entry*)entry)->name);
		entry = entry->next;
	}*/
}

void reset_table() {
	table_ptr *tmp;
	if(cur_table != NULL)
	while (cur_table != NULL && cur_table->father != NULL) {
		 //free entry data structure????
								//free hash table?
		zfree_hash_table(cur_table->unused);
		zfree_hash_table(cur_table->used);

		tmp = cur_table;
		cur_table = cur_table->father;
		free(tmp);
	}
	if (cur_table != NULL) {
		; //free entry data structure????
								//free hash table?
		zfree_hash_table(cur_table->unused);
		zfree_hash_table(cur_table->used);
	}

	cur_table = NULL;
}
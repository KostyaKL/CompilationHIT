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

table_ptr *make_table(table_ptr *current_table, int line) {
	table_ptr *tmp;
	char tmp_line[10];
	char tmp_scope[10];

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
		current_table->scope_number = 0;
		current_table->ids = (ids_list*)malloc(sizeof(ids_list));
		current_table->ids->prev = NULL;
		current_table->ids->id = NULL;

		//zhash_set(current_table->unused, "0", NULL);
		
		itoa(line, tmp_line, 10);
		char *msg[2] = { "start global scope at line: ", tmp_line };
		//print_sem(msg, 2);
		
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
	tmp->scope_number = current_table->scope_number + 1;
	tmp->ids = (ids_list*)malloc(sizeof(ids_list));
	tmp->ids->prev = NULL;
	tmp->ids->id = NULL;

	//zhash_set(tmp->unused, "0", NULL);

	itoa(line, tmp_line, 10);
	itoa(tmp->scope_number, tmp_scope, 10);
	char *msg[4] = { "start scope number: ", tmp_scope," at line: ", tmp_line };
	//print_sem(msg, 4);

	return tmp;
}

table_ptr *pop_table(table_ptr *current_table, int line) {
	table_ptr *tmp;
	int is_unused_exist = is_unused(current_table);
	if (is_unused_exist) {
		print_unused(current_table);
	}

	//free(current_table->entry); //free entry data structure????
								//free hash table?
	tmp = current_table->father;

	if (tmp != NULL && current_table->scope_number) {
		char tmp_line[10];
		char tmp_scope[10];
		itoa(line, tmp_line, 10);
		itoa(current_table->scope_number, tmp_scope, 10);
		char *msg[4] = { "end scope number: ", tmp_scope," at line: ", tmp_line };
		//print_sem(msg, 4);
	}
	else {
		char tmp_line[10];
		itoa(line, tmp_line, 10);
		char *msg[2] = { "end global scope at line: ", tmp_line };
		//print_sem(msg, 2);
	}
	free(current_table);
	return tmp;
}

table_entry *insert(table_ptr *current_table, char *id_name, int line) {
	table_entry *new_entry;
	new_entry = lookup(current_table, id_name);
	if (new_entry != NULL) {
		fprintf(semantic_report, "ERROR line %d: duplicated declaration of the same name: %s \n", line, id_name);
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
	new_entry->size = 0;
	new_entry->type = NULL_type;
	new_entry->param_num = 0;
	new_entry->line_number = line;

	current_table->ids->id = (char*)calloc(sizeof(char),strlen(id_name));
	strcat(current_table->ids->id, id_name);
	ids_list *tmp = (ids_list*)malloc(sizeof(ids_list));
	tmp->prev = current_table->ids;
	tmp->id = NULL;
	current_table->ids = tmp;
	zhash_set(current_table->unused, id_name, new_entry);

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
				id_entry = use_id(tab, id_name);
			}
			return (id_entry);
		}
		else
			tab = tab->father;
	}
	fprintf(semantic_report, "ERROR line %d: undeclared identifier: %s \n", line, id_name);
	return NULL;
}

void set_id_type(table_entry *id_entry, elm_type id_type) {
	id_entry->type = id_type;
}

elm_type get_id_type(table_entry *id_entry) {
	return id_entry->type;
}

table_entry *use_id(table_ptr *current_table, char *id_name) {
	table_entry *tmp = NULL;
	table_entry *new_entry = NULL;
	tmp = zhash_get(current_table->unused, id_name);
	if (tmp != NULL) {
		new_entry = (table_entry*)malloc(sizeof(table_entry));
		new_entry->is_function = tmp->is_function;
		new_entry->name = tmp->name;
		new_entry->num_of_parameters = tmp->num_of_parameters;
		new_entry->parameters_list = tmp->parameters_list;
		new_entry->param_num = tmp->param_num;
		new_entry->return_type = tmp->return_type;
		new_entry->size = tmp->size;
		new_entry->type = tmp->type;
		zhash_set(current_table->used, new_entry->name, new_entry);
		zhash_delete(current_table->unused, id_name);
	}
	return zhash_get(current_table->used, id_name);
}

int is_unused(table_ptr *current_table) {
	if (current_table->unused->entry_count == 0) {
		return 0;
	}
	return 1;
}

void print_unused(table_ptr *current_table) {
	table_entry *entry = NULL;
	fprintf(semantic_report, "ERROR scope %d: there is %d unsused ids:\n", current_table->scope_number, current_table->unused->entry_count );
	
	ids_list *tmp = current_table->ids;
	while (tmp != NULL) {
		if(tmp->id != NULL)
		entry = zhash_get(current_table->unused, tmp->id);
		if (entry != NULL) {
			fprintf(semantic_report, "\tline: %d, id: %s\n", entry->line_number, entry->name);
		}
		tmp = tmp->prev;
	}
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
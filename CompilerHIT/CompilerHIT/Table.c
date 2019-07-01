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
		cur_table->entry = NULL;
		return cur_table;
	}

	tmp = (table_ptr*)malloc(sizeof(table_ptr));
	if (tmp == NULL)
	{
		fprintf(semantic_report, "\nUnable to allocate memory! \n");
		exit(0);
	}
	tmp->father = current_table;
	tmp->entry = NULL;
	return tmp;

}

table_ptr *pop_table(table_ptr *current_table) {

}

table_entry *insert(table_ptr *current_table, char *id_name) {

}

table_entry *lookup(table_ptr *current_table, char *id_name) {

}

table_entry *find(table_ptr *current_table, char *id_name) {

}

void set_id_type(table_entry *id_entry, elm_type id_type) {

}

elm_type get_id_type(table_entry *id_entry) {

}

void reset_table() {
	table_ptr *tmp;
	while (cur_table->father != NULL) {
		free(cur_table->entry); //free entry data structure????
		tmp = cur_table;
		cur_table = cur_table->father;
		free(tmp);
	}
	free(cur_table->entry); //free entry data structure????
}
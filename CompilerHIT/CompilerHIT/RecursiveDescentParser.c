#include "Parser.h"

void parser() { /*main parser methond*/
	parse_program(); /*parser start rule of grammar*/
	match(TOKEN_EOF); /*check that parser is actually is finished on EOF*/
}

void parse_program() { /*one case rule*/
	print_parser_rule("PROGRAM -> program VAR_DEFINITIONS ; STATMENTS end FUNC_DEFINITIONS");

	cur_table = make_table(cur_table, 1);

	match(TOKEN_PROGRAM);

	cur_table = make_table(cur_table, cur_token->lineNumber);

	parse_var_definitions(NULL);
	match(TOKEN_SEMICOLON);
	parse_statments(NULL);
	match(TOKEN_END);

	cur_table = pop_table(cur_table, cur_token->lineNumber);

	cur_table = make_table(cur_table, cur_token->lineNumber);

	parse_func_definitions();

	cur_table = pop_table(cur_table, cur_token->lineNumber);

	cur_table = pop_table(cur_table, cur_token->lineNumber);
}

void parse_var_definitions(table_entry *entry) {
	cur_token = next_token();
	eTOKENS expected[2] = { TOKEN_REAL, TOKEN_INTEGER }; /*expected tokens for error printing purpose*/
	switch (cur_token->kind)
	{
	case TOKEN_REAL:
		print_parser_rule("VAR_DEFINITIONS -> VAR_DEFINITION VAR_DEFINITIONS_CLEAN");
		cur_token = back_token();
		parse_var_definition(entry);
		parse_var_definitions_clean(entry);
		break;
	case TOKEN_INTEGER:
		print_parser_rule("VAR_DEFINITIONS -> VAR_DEFINITION VAR_DEFINITIONS_CLEAN");
		cur_token = back_token();
		parse_var_definition(entry);
		parse_var_definitions_clean(entry);
		break;
	default:
		error_recovery(VAR_DEFINITIONS, expected, 2); /*print error and try to recover*/
		break;
	}
}

void parse_var_definitions_clean(table_entry *entry) {
	next_token();
	Token *peek = next_token();
	eTOKENS expected[2] = { TOKEN_SEMICOLON, TOKEN_CLOSE_CIRCULAR_PAR }; /*expected tokens for error printing purpose*/
	cur_token = back_token();
	switch (cur_token->kind)
	{
	case TOKEN_SEMICOLON:
		if (peek->kind == TOKEN_REAL || peek->kind == TOKEN_INTEGER) {
			print_parser_rule("VAR_DEFINITIONS_CLEAN -> ; VAR_DEFINITIONS");
			parse_var_definitions(entry);
		}
		else {
			print_parser_rule("VAR_DEFINITIONS_CLEAN -> epsilon");
			cur_token = back_token();
		}
		break;
	case TOKEN_CLOSE_CIRCULAR_PAR:
		print_parser_rule("VAR_DEFINITIONS_CLEAN -> epsilon");
		cur_token = back_token();
		break;
	default:
		error_recovery(VAR_DEFINITIONS_CLEAN, expected, 2); /*print error and try to recover*/
		break;
	}
}

void parse_var_definition(table_entry *entry) {
	cur_token = next_token();
	eTOKENS expected[2] = { TOKEN_REAL, TOKEN_INTEGER }; /*expected tokens for error printing purpose*/
	elm_type type;
	switch (cur_token->kind)
	{
	case TOKEN_REAL:
		print_parser_rule("VAR_DEFINITION -> TYPE VARIABLES_LIST");
		cur_token = back_token();
		type = parse_type();
		parse_variables_list(type, entry, 0);
		break;
	case TOKEN_INTEGER:
		print_parser_rule("VAR_DEFINITION -> TYPE VARIABLES_LIST");
		cur_token = back_token();
		type = parse_type();
		parse_variables_list(type, entry, 0);
		break;
	default:
		error_recovery(VAR_DEFINITION, expected, 2); /*print error and try to recover*/
		break;
	}
}

elm_type parse_type() {
	cur_token = next_token();
	eTOKENS expected[2] = { TOKEN_REAL, TOKEN_INTEGER }; /*expected tokens for error printing purpose*/
	switch (cur_token->kind)
	{
	case TOKEN_REAL:
		print_parser_rule("TYPE -> real");
		return REAL;
		break;
	case TOKEN_INTEGER:
		print_parser_rule("TYPE -> integer");
		return INTEGER;
		break;
	default:
		error_recovery(TYPE, expected, 2); /*print error and try to recover*/
		break;
	}
	return NULL_type;
}

int parse_variables_list(elm_type type, table_entry *entry, int param_list) { /*one case rule*/
	print_parser_rule("VARIABLES_LIST -> VARIABLE VARIABLES_LIST_CLEAN");
	match(TOKEN_ID);
	cur_token = back_token();
	parse_variable(type, entry, param_list, 0);
	return parse_variables_list_clean(type, entry, param_list, 0);
}

int parse_variables_list_clean(elm_type type, table_entry *entry, int param_list, int index) {
	cur_token = next_token();
	eTOKENS expected[3] = { TOKEN_COMMA, TOKEN_SEMICOLON, TOKEN_CLOSE_CIRCULAR_PAR }; /*expected tokens for error printing purpose*/
	switch (cur_token->kind)
	{
	case TOKEN_COMMA:
		print_parser_rule("VARIABLES_LIST_CLEAN -> , VARIABLE VARIABLES_LIST_CLEAN");
		index = parse_variable(type, entry, param_list, index);
		index = parse_variables_list_clean(type, entry, param_list, index);
		break;
	case TOKEN_SEMICOLON:
		print_parser_rule("VARIABLES_LIST_CLEAN -> epsilon");
		cur_token = back_token();
		break;
	case TOKEN_CLOSE_CIRCULAR_PAR:
		print_parser_rule("VARIABLES_LIST_CLEAN -> epsilon");
		cur_token = back_token();
		break;
	default:
		error_recovery(VARIABLES_LIST_CLEAN, expected, 3); /*print error and try to recover*/
		break;
	}
}

int parse_variable(elm_type type, table_entry *entry_func, int param_list, int index) { /*one case rule*/
	table_entry *entry = NULL, *defined = NULL;
	int size = 0;
	int i = 1;
	char *id;
	int line_num = cur_token->lineNumber;
	char line[10];
	print_parser_rule("VARIABLE -> id VARIABLE_CLEAN");
	match(TOKEN_ID);
	id = cur_token->lexeme;;
	if (cur_token->kind == TOKEN_ID && param_list == 0) {
		entry = insert(cur_table, cur_token->lexeme, cur_token->lineNumber);
	}
	size = parse_variable_clean();
	if (size) {
		size -= 10;
	}

	if (entry != NULL && param_list == 0) {
		set_id_type(entry, type);
		entry->size = size;
		char tmp[10];
		itoa(size, tmp, 10);
		char *msg[6] = { "\ttype: ", getTypeName(type), " id: ", entry->name, " size: ", tmp };
		//print_sem(msg, 6);

		//func argument
		if (entry_func != NULL) {
			entry_func->num_of_parameters += 1;
			entry->param_num = entry_func->num_of_parameters;
			char tmp[10];
			itoa(index + 1, tmp, 10);
			zhash_set(entry_func->parameters_list, tmp, entry);
		}
	}

	if (param_list) {
		entry = find(cur_table, id, line_num, 1);
		if (entry == NULL) {
			itoa(line_num, line, 10);
			char *msg[5] = { "\tERROR line ", line, ": no definition for id: ", id, " in function" };
			print_sem(msg, 5);
		}
		if (entry_func == NULL) {
			itoa(line_num, line, 10);
			char *msg[3] = { "\tERROR line ", line, ": no definition for function " };
			//print_sem(msg, 3);
		}
		else {
			char tmp[10];
			itoa(index + 1, tmp, 10);
			defined = zhash_get(entry_func->parameters_list, tmp);
			if (index + 1 > entry_func->num_of_parameters) {
				itoa(line_num, line, 10);
				char *msg[3] = { "\tERROR line ", line, ": wrong number of parameters" };
				print_sem(msg, 3);
			}
			else if (defined->type != entry->type) {
				itoa(line_num, line, 10);
				char *msg[3] = { "\tERROR line ", line, ": wrong argument type" };
				print_sem(msg, 3);
			}
		}
	}
	return index + 1;
}

int parse_variable_clean() {
	int ret, i = 1;
	char * tmp;
	cur_token = next_token();
	eTOKENS expected[5] = { TOKEN_OPEN_SQUER_PAR, TOKEN_ASSIGNMENT, TOKEN_COMMA, TOKEN_SEMICOLON, TOKEN_CLOSE_CIRCULAR_PAR }; /*expected tokens for error printing purpose*/
	switch (cur_token->kind)
	{
	case TOKEN_OPEN_SQUER_PAR:
		print_parser_rule("VARIABLE_CLEAN -> [ int_number ]");
		match(TOKEN_INT_NUMBER);
		tmp = cur_token->lexeme;
		match(TOKEN_CLOSE_SQUER_PAR);

		ret = tmp[0] - 48;
		while (tmp[i] != '\0') {
			ret *= 10;
			ret += tmp[i] - 48;
			i++;
		}

		return ret + 10;
		break;
	case TOKEN_ASSIGNMENT:
		print_parser_rule("VARIABLE_CLEAN -> epsilon");
		cur_token = back_token();
		break;
	case TOKEN_COMMA:
		print_parser_rule("VARIABLE_CLEAN -> epsilon");
		cur_token = back_token();
		break;
	case TOKEN_SEMICOLON:
		print_parser_rule("VARIABLE_CLEAN -> epsilon");
		cur_token = back_token();
		break;
	case TOKEN_CLOSE_CIRCULAR_PAR:
		print_parser_rule("VARIABLE_CLEAN -> epsilon");
		cur_token = back_token();
		break;
	default:
		error_recovery(VARIABLE_CLEAN, expected, 5); /*print error and try to recover*/
		break;
	}
	return 0;
}

void parse_func_definitions() {
	cur_token = next_token();
	eTOKENS expected[3] = { TOKEN_REAL, TOKEN_INTEGER, TOKEN_VOID }; /*expected tokens for error printing purpose*/
	switch (cur_token->kind)
	{
	case TOKEN_REAL:
		print_parser_rule("FUNC_DEFINITIONS -> FUNC_DEFINITION FUNC_DEFINITIONS_CLEAN");
		cur_token = back_token();
		parse_func_definition();
		parse_func_definitions_celan();
		break;
	case TOKEN_INTEGER:
		print_parser_rule("FUNC_DEFINITIONS -> FUNC_DEFINITION FUNC_DEFINITIONS_CLEAN");
		cur_token = back_token();
		parse_func_definition();
		parse_func_definitions_celan();
		break;
	case TOKEN_VOID:
		print_parser_rule("FUNC_DEFINITIONS -> FUNC_DEFINITION FUNC_DEFINITIONS_CLEAN");
		cur_token = back_token();
		parse_func_definition();
		parse_func_definitions_celan();
		break;
	default:
		error_recovery(FUNC_DEFINITIONS, expected, 3); /*print error and try to recover*/
		break;
	}
}

void parse_func_definitions_celan() {
	cur_token = next_token();
	eTOKENS expected[4] = { TOKEN_REAL, TOKEN_INTEGER, TOKEN_VOID, TOKEN_EOF }; /*expected tokens for error printing purpose*/
	switch (cur_token->kind)
	{
	case TOKEN_REAL:
		print_parser_rule("FUNC_DEFINITIONS_CLEAN -> FUNC_DEFINITION FUNC_DEFINITIONS_CLEAN");
		cur_token = back_token();
		parse_func_definition();
		parse_func_definitions_celan();
		break;
	case TOKEN_INTEGER:
		print_parser_rule("FUNC_DEFINITIONS_CLEAN -> FUNC_DEFINITION FUNC_DEFINITIONS_CLEAN");
		cur_token = back_token();
		parse_func_definition();
		parse_func_definitions_celan();
		break;
	case TOKEN_VOID:
		print_parser_rule("FUNC_DEFINITIONS_CLEAN -> FUNC_DEFINITION FUNC_DEFINITIONS_CLEAN");
		cur_token = back_token();
		parse_func_definition();
		parse_func_definitions_celan();
		break;
	case TOKEN_EOF:
		print_parser_rule("FUNC_DEFINITIONS_CLEAN -> epsilon");
		cur_token = back_token();
		break;
	default:
		error_recovery(FUNC_DEFINITIONS_CLEAN, expected, 4); /*print error and try to recover*/
		break;
	}
}

void parse_func_definition() {
	int ret;
	cur_token = next_token();
	eTOKENS expected[3] = { TOKEN_REAL, TOKEN_INTEGER, TOKEN_VOID }; /*expected tokens for error printing purpose*/
	elm_type type;
	table_entry *entry = NULL;
	
	switch (cur_token->kind)
	{
	case TOKEN_REAL:
		print_parser_rule("FUNC_DEFINITION -> RETURNED_TYPE id ( PARAM_DEFINITIONS ) BLOCK");
		cur_token = back_token();
		type = parse_returned_type();
		match(TOKEN_ID);
		if (cur_token->kind == TOKEN_ID) {
			entry = insert(cur_table, cur_token->lexeme, cur_token->lineNumber);
			if (entry != NULL) {
				entry->is_function = 1;
				entry->parameters_list = zcreate_hash_table();
				entry->type = type;
				entry->return_type = type;
				cur_table = make_table(cur_table, cur_token->lineNumber);
			}
		}
		match(TOKEN_OPEN_CIRCULAR_PAR);
		parse_param_definitions(entry);
		match(TOKEN_CLOSE_CIRCULAR_PAR);
		ret = parse_block(entry);
		if (entry != NULL && entry->return_type != NULL_type && ret == 0) {
			char line[10];
			itoa(cur_token->lineNumber, line, 10);
			char *msg[4] = { "\tERROR line ", line, ": return type doesn't match function: ", entry->name };
			print_sem(msg, 4);
		}
		break;
	case TOKEN_INTEGER:
		print_parser_rule("FUNC_DEFINITION -> RETURNED_TYPE id ( PARAM_DEFINITIONS ) BLOCK");
		cur_token = back_token();
		type = parse_returned_type();
		match(TOKEN_ID);
		if (cur_token->kind == TOKEN_ID) {
			entry = insert(cur_table, cur_token->lexeme, cur_token->lineNumber);
			if (entry != NULL) {
				entry->is_function = 1;
				entry->parameters_list = zcreate_hash_table();
				entry->type = type;
				entry->return_type = type;
				cur_table = make_table(cur_table, cur_token->lineNumber);
			}
		}
		match(TOKEN_OPEN_CIRCULAR_PAR);
		parse_param_definitions(entry);
		match(TOKEN_CLOSE_CIRCULAR_PAR);
		ret = parse_block(entry);
		if (entry != NULL && entry->return_type != NULL_type && ret == 0) {
			char line[10];
			itoa(cur_token->lineNumber, line, 10);
			char *msg[4] = { "\tERROR line ", line, ": return type doesn't match function: ", entry->name };
			print_sem(msg, 4);
		}
		break;
	case TOKEN_VOID:
		print_parser_rule("FUNC_DEFINITION -> RETURNED_TYPE id ( PARAM_DEFINITIONS ) BLOCK");
		cur_token = back_token();
		type = parse_returned_type();
		match(TOKEN_ID);
		if (cur_token->kind == TOKEN_ID) {
			entry = insert(cur_table, cur_token->lexeme, cur_token->lineNumber);
			if (entry != NULL) {
				entry->is_function = 1;
				entry->parameters_list = zcreate_hash_table();
				entry->type = type;
				entry->return_type = type;
				cur_table = make_table(cur_table, cur_token->lineNumber);
			}
		}
		match(TOKEN_OPEN_CIRCULAR_PAR);
		parse_param_definitions(entry);
		match(TOKEN_CLOSE_CIRCULAR_PAR);
		ret = parse_block(entry);
		if (entry != NULL && entry->return_type != NULL_type && ret == 0) {
			char line[10];
			itoa(cur_token->lineNumber, line, 10);
			char *msg[4] = { "\tERROR line ", line, ": return type doesn't match function: ", entry->name };
			print_sem(msg, 4);
		}
		break;
	default:
		error_recovery(FUNC_DEFINITION, expected, 3); /*print error and try to recover*/
		break;
	}

	if (entry != NULL) {
		cur_table = pop_table(cur_table, cur_token->lineNumber);
		set_id_type(entry, type);
		char noa[2] = { (char)(entry->num_of_parameters + 48) , '\0' };
		char *msg[6] = { "\ttype: ", getTypeName(type), " id: ", entry->name, " num of arg: ", noa };
		//print_sem(msg, 6);
		
	}
}

elm_type parse_returned_type() {
	cur_token = next_token();
	eTOKENS expected[3] = { TOKEN_REAL, TOKEN_INTEGER, TOKEN_VOID }; /*expected tokens for error printing purpose*/
	switch (cur_token->kind)
	{
	case TOKEN_REAL:
		print_parser_rule("RETURNED_TYPE -> TYPE");
		cur_token = back_token();
		return parse_type();
		break;
	case TOKEN_INTEGER:
		print_parser_rule("RETURNED_TYPE -> TYPE");
		cur_token = back_token();
		return parse_type();
		break;
	case TOKEN_VOID:
		print_parser_rule("RETURNED_TYPE -> void");
		break;
	default:
		error_recovery(RETURNED_TYPE, expected, 3); /*print error and try to recover*/
		break;
	}
	return NULL_type;
}

void parse_param_definitions(table_entry *entry) {
	cur_token = next_token();
	eTOKENS expected[3] = { TOKEN_REAL, TOKEN_INTEGER, TOKEN_CLOSE_CIRCULAR_PAR }; /*expected tokens for error printing purpose*/
	switch (cur_token->kind)
	{
	case TOKEN_REAL:
		print_parser_rule("PARAM_DEFINITIONS -> VAR_DEFINITIONS");
		cur_token = back_token();
		parse_var_definitions(entry);
		break;
	case TOKEN_INTEGER:
		print_parser_rule("PARAM_DEFINITIONS -> VAR_DEFINITIONS");
		cur_token = back_token();
		parse_var_definitions(entry);
		break;
	case TOKEN_CLOSE_CIRCULAR_PAR:
		print_parser_rule("PARAM_DEFINITIONS -> epsilon");
		cur_token = back_token();
		break;
	default:
		error_recovery(PARAM_DEFINITIONS, expected, 3); /*print error and try to recover*/
		break;
	}
}

int parse_statments(table_entry *entry) {
	cur_token = next_token();
	int ret = 0;
	eTOKENS expected[3] = { TOKEN_ID, TOKEN_RETURN, TOKEN_OPEN_CURLY_PAR }; /*expected tokens for error printing purpose*/
	switch (cur_token->kind)
	{
	case TOKEN_ID:
		print_parser_rule("STATEMENTS -> STATEMENT ; STATEMENTS_CLEAN");
		cur_token = back_token();
		ret = parse_statment(entry);
		match(TOKEN_SEMICOLON);
		if (ret) {
			parse_statments_clean(entry);
		}
		else {
			ret = parse_statments_clean(entry);
		}
		return ret;
		break;
	case TOKEN_RETURN:
		print_parser_rule("STATEMENTS -> STATEMENT ; STATEMENTS_CLEAN");
		cur_token = back_token();
		parse_statment(entry);
		match(TOKEN_SEMICOLON);
		if (ret) {
			parse_statments_clean(entry);
		}
		else {
			ret = parse_statments_clean(entry);
		}
		return ret;
		break;
	case TOKEN_OPEN_CURLY_PAR:
		print_parser_rule("STATEMENTS -> STATEMENT ; STATEMENTS_CLEAN");
		cur_token = back_token();
		parse_statment(entry);
		match(TOKEN_SEMICOLON);
		if (ret) {
			parse_statments_clean(entry);
		}
		else {
			ret = parse_statments_clean(entry);
		}
		return ret;
		break;
	default:
		error_recovery(STATEMENTS, expected, 3); /*print error and try to recover*/
		break;
	}
	return ret;
}

int parse_statments_clean(table_entry *entry) {
	cur_token = next_token();
	eTOKENS expected[5] = { TOKEN_ID, TOKEN_RETURN, TOKEN_OPEN_CURLY_PAR, TOKEN_END, TOKEN_CLOSE_CURLY_PAR }; /*expected tokens for error printing purpose*/
	switch (cur_token->kind)
	{
	case TOKEN_ID:
		print_parser_rule("STATEMENTS_CLEAN -> STATMENTS");
		cur_token = back_token();
		return parse_statments(entry);
		break;
	case TOKEN_RETURN:
		print_parser_rule("STATEMENTS_CLEAN -> STATMENTS");
		cur_token = back_token();
		return parse_statments(entry);
		break;
	case TOKEN_OPEN_CURLY_PAR:
		print_parser_rule("STATEMENTS_CLEAN -> STATMENTS");
		cur_token = back_token();
		return parse_statments(entry);
		break;
	case TOKEN_END:
		print_parser_rule("STATEMENTS_CLEAN -> epsilon");
		cur_token = back_token();
		break;
	case TOKEN_CLOSE_CURLY_PAR:
		print_parser_rule("STATEMENTS_CLEAN -> epsilon");
		cur_token = back_token();
		break;
	default:
		error_recovery(STATEMENTS_CLEAN, expected, 5); /*print error and try to recover*/
		break;
	}
	return 0;
}

int parse_statment(table_entry *entry_func) {
	cur_token = next_token();
	int *statment;
	char *toke_not_found;
	elm_type id_type;
	table_entry *entry;
	eTOKENS expected[3] = { TOKEN_ID, TOKEN_RETURN, TOKEN_OPEN_CURLY_PAR }; /*expected tokens for error printing purpose*/
	switch (cur_token->kind)
	{
	case TOKEN_ID:
		print_parser_rule("STATEMENT -> id ID_STATEMENT_CLEAN");
		if (entry_func == NULL) {
			entry = find(cur_table, cur_token->lexeme, cur_token->lineNumber, 1);
		}
		else {
			entry = find(cur_table, cur_token->lexeme, cur_token->lineNumber, 1);
		}
		toke_not_found = cur_token->lexeme;
		statment = parse_id_statment_clean(entry_func);
		if (entry == NULL) {
			return 0;
		}
		else if (statment[2] == 1){
			id_type = get_id_type(entry);
			if (entry->size > 0 && statment[0] == -1) {
				char line[10];
				itoa(cur_token->lineNumber, line, 10);
				char *msg[4] = { "\tERROR line ", line, ": no index for array: ", entry->name };
				print_sem(msg, 4);
				//return id_type;
			}
			else if (entry->size > 0 && (statment[0] < 0 || statment[0] >= entry->size)) {
				char line[10];
				itoa(cur_token->lineNumber, line, 10);
				char *msg[4] = { "\tERROR line ", line, ": index out of range for array: ", entry->name };
				print_sem(msg, 4);
				//return id_type;
			}
			else if (statment[1] == NULL_type || id_type == NULL_type) {
				//error bad type of elements
				char line[10];
				itoa(cur_token->lineNumber, line, 10);
				char *msg[3] = { "\tERROR line ", line, ": one or more elements with no defined type" };
				print_sem(msg, 3);
				//return NULL_type;
			}
			else if (statment[1] == INTEGER && id_type == INTEGER) {
				//return INTEGER;
			}
			else if (statment[1] == REAL && id_type == REAL) {
				//return REAL;
			}
			else {
				char line[10];
				itoa(cur_token->lineNumber, line, 10);
				char *msg[4] = { "\tERROR line ", line, ": expression doesn't match type of variable: ", entry->name };
				print_sem(msg, 4);
				//return NULL_type;
			}
		}
		break;
	case TOKEN_RETURN:
		print_parser_rule("STATEMENT -> return RETURN_STATEMENT_CLEAN");
		return parse_return_statment_clean(entry_func);
		break;
	case TOKEN_OPEN_CURLY_PAR:
		print_parser_rule("STATEMENT -> BLOCK");
		cur_token = back_token();

		cur_table = make_table(cur_table, cur_token->lineNumber);

		parse_block(entry_func);

		cur_table = pop_table(cur_table, cur_token->lineNumber);
		break;
	default:
		error_recovery(STATEMENT, expected, 3); /*print error and try to recover*/
		break;
	}
	return 0;
}

int parse_return_statment_clean(table_entry * entry) {
	cur_token = next_token();
	elm_type type = NULL_type;
	eTOKENS expected[4] = { TOKEN_ID, TOKEN_INT_NUMBER, TOKEN_REAL_NUMBER, TOKEN_SEMICOLON }; /*expected tokens for error printing purpose*/
	switch (cur_token->kind)
	{
	case TOKEN_ID:
		print_parser_rule("RETURN_STATEMENT_CLEAN -> EXPRESSION");
		cur_token = back_token();
		type = parse_expression();
		if (entry != NULL && type != entry->type && entry->return_type != NULL_type) {
			char line[10];
			itoa(cur_token->lineNumber, line, 10);
			char *msg[4] = { "\tERROR line ", line, ": return type doesn't match function: ", entry->name  };
			print_sem(msg, 4);
		}
		break;
	case TOKEN_INT_NUMBER:
		print_parser_rule("RETURN_STATEMENT_CLEAN -> EXPRESSION");
		cur_token = back_token();
		type = parse_expression();
		if (entry != NULL && type != entry->type && entry->return_type != NULL_type) {
			char line[10];
			itoa(cur_token->lineNumber, line, 10);
			char *msg[4] = { "\tERROR line ", line, ": return type doesn't match function: ", entry->name };
			print_sem(msg, 4);
		}		break;
	case TOKEN_REAL_NUMBER:
		print_parser_rule("RETURN_STATEMENT_CLEAN -> EXPRESSION");
		cur_token = back_token();
		type = parse_expression();
		if (entry != NULL && type != entry->type && entry->return_type != NULL_type) {
			char line[10];
			itoa(cur_token->lineNumber, line, 10);
			char *msg[4] = { "\tERROR line ", line, ": return type doesn't match function: ", entry->name };
			print_sem(msg, 4);
		}		break;
	case TOKEN_SEMICOLON:
		print_parser_rule("RETURN_STATEMENT_CLEAN -> epsilon");
		cur_token = back_token();
		if (entry != NULL && type != entry->type && entry->return_type != NULL_type) {
			char line[10];
			itoa(cur_token->lineNumber, line, 10);
			char *msg[4] = { "\tERROR line ", line, ": return type doesn't match function: ", entry->name };
			print_sem(msg, 4);
		}
		break;
	default:
		error_recovery(RETURN_STATEMENT_CLEAN, expected, 4); /*print error and try to recover*/
		return 0;
		break;
	}
	return 1;
}

int *parse_id_statment_clean(table_entry *entry) {
	cur_token = next_token();
	elm_type var_c_type, exp_type;
	int *ret = (int*)malloc(3 * sizeof(int));
	int param_count = 0;
	eTOKENS expected[3] = { TOKEN_OPEN_SQUER_PAR, TOKEN_OPEN_CIRCULAR_PAR, TOKEN_ASSIGNMENT }; /*expected tokens for error printing purpose*/
	switch (cur_token->kind)
	{
	case TOKEN_OPEN_SQUER_PAR:
		print_parser_rule("ID_STATEMENT_CLEAN -> VARIABLE_CLEAN = EXPRESSION");
		if (entry != NULL && entry->is_function) {
			char line[10];
			itoa(cur_token->lineNumber, line, 10);
			char *msg[4] = { "\tERROR line ", line, ": illegal address as an array for function: ", entry->name };
			print_sem(msg, 4);
		}
		cur_token = back_token();
		var_c_type = parse_variable_clean();
		if (var_c_type) {
			var_c_type -= 10;
		}
		else {
			var_c_type = -1;
		}
		match(TOKEN_ASSIGNMENT);
		exp_type = parse_expression();
		ret[0] = var_c_type;
		ret[1] = exp_type;
		ret[2] = 1;
		return ret;
		break;
	case TOKEN_ASSIGNMENT:
		print_parser_rule("ID_STATEMENT_CLEAN -> VARIABLE_CLEAN = EXPRESSION");
		if (entry != NULL && entry->is_function) {
			char line[10];
			itoa(cur_token->lineNumber, line, 10);
			char *msg[4] = { "\tERROR line ", line, ": illegal assignment for function: ", entry->name };
			print_sem(msg, 4);
		}
		cur_token = back_token();
		var_c_type = parse_variable_clean();
		if (var_c_type) {
			var_c_type -= 10;
		}
		else {
			var_c_type = -1;
		}
		match(TOKEN_ASSIGNMENT);
		exp_type = parse_expression();
		ret[0] = var_c_type;
		ret[1] = exp_type;
		ret[2] = 1;
		return ret;
		break;
	case TOKEN_OPEN_CIRCULAR_PAR:
		print_parser_rule("ID_STATEMENT_CLEAN -> ( PARAMETERS_LIST )");
		param_count = parse_parameters_list(entry);
		if (entry != NULL && param_count != entry->param_num) {
			char line[10];
			itoa(cur_token->lineNumber, line, 10);
			char *msg[3] = { "\tERROR line ", line, ": wrong number of parameters" };
			print_sem(msg, 3);
		}
		match(TOKEN_CLOSE_CIRCULAR_PAR);
		ret[2] = 0;
		return ret;		
		break;
	default:
		error_recovery(ID_STATEMENT_CLEAN, expected, 3); /*print error and try to recover*/
		break;
	}
	ret[0] = 0;
	ret[1] = 0;
	ret[2] = 0;
	return ret;
}

int parse_block(table_entry * entry) { /*one case rule*/
	int ret = 0;
	print_parser_rule("BLOCK -> { VAR_DEFINITIONS ; STATMENTS }");
	match(TOKEN_OPEN_CURLY_PAR);
	parse_var_definitions(NULL);
	match(TOKEN_SEMICOLON);
	ret = parse_statments(entry);
	match(TOKEN_CLOSE_CURLY_PAR);
	/*if (entry != NULL && entry->return_type != NULL_type && ret == 0) {
		char line[10];
		itoa(cur_token->lineNumber, line, 10);
		char *msg[3] = { "\tERROR line ", line, ": return type don't match" };
		print_sem(msg, 3);
	}*/
	return ret;
}

int parse_parameters_list(table_entry *entry) {
	cur_token = next_token();
	eTOKENS expected[2] = { TOKEN_ID, TOKEN_CLOSE_CIRCULAR_PAR }; /*expected tokens for error printing purpose*/
	switch (cur_token->kind)
	{
	case TOKEN_ID:
		print_parser_rule("PARAMETERS_LIST -> VARIABLES_LIST");
		cur_token = back_token();
		return parse_variables_list(0, entry, 1);
		break;
	case TOKEN_CLOSE_CIRCULAR_PAR:
		print_parser_rule("PARAMETERS_LIST -> epsilon");
		cur_token = back_token();
		break;
	default:
		error_recovery(PARAMETERS_LIST, expected, 2); /*print error and try to recover*/
		break;
	}
	return 0;
}

elm_type parse_expression() {
	elm_type exp_type, id_type;
	table_entry *entry;
	char *toke_not_found;
	cur_token = next_token();
	eTOKENS expected[3] = { TOKEN_ID, TOKEN_INT_NUMBER, TOKEN_REAL_NUMBER }; /*expected tokens for error printing purpose*/
	switch (cur_token->kind)
	{
	case TOKEN_ID:
		print_parser_rule("EXPRESSION -> id EXPRESSION_CLEAN");
		entry = find(cur_table, cur_token->lexeme, cur_token->lineNumber, 1);
		toke_not_found = cur_token->lexeme;
		exp_type = parse_expression_clean();
		if (entry == NULL) {
			return NULL_type;
		}
		else {
			id_type = get_id_type(entry);
			if (entry->size > 0 && exp_type < 8) {
				char line[10];
				itoa(cur_token->lineNumber, line, 10);
				char *msg[4] = { "\tERROR line ", line, ": no index for array: ", entry->name };
				print_sem(msg, 4);
				return id_type;
			}
			else if (entry->size > 0 && exp_type > 3) {
				exp_type -= 10;
				if (exp_type < 0 || exp_type >= entry->size) {
					char line[10];
					itoa(cur_token->lineNumber, line, 10);
					char *msg[4] = { "\tERROR line ", line, ": index out of range for array: ", entry->name };
					print_sem(msg, 4);
				}
				return id_type;
			}
			else if (exp_type == NULL_type || id_type == NULL_type) {
				//error bad type of elements
				char line[10];
				itoa(cur_token->lineNumber, line, 10);
				char *msg[3] = { "\tERROR line ", line, ": on or more elements with no defined type"};
				print_sem(msg, 3);
				return NULL_type;
			}
			else if (exp_type == INTEGER && id_type == INTEGER) {
				return INTEGER;
			}
			else {
				return REAL;
			}
		}

		break;
	case TOKEN_INT_NUMBER:
		print_parser_rule("EXPRESSION -> int_number");
		return INTEGER;
		break;
	case TOKEN_REAL_NUMBER:
		print_parser_rule("EXPRESSION -> real_number");
		return REAL;
		break;
	default:
		error_recovery(EXPRESSION, expected, 3); /*print error and try to recover*/
		break;
	}
	return NULL_type;
}

elm_type parse_expression_clean() {
	cur_token = next_token();
	eTOKENS expected[5] = { TOKEN_SEMICOLON, TOKEN_OPEN_SQUER_PAR, TOKEN_MUL, TOKEN_DIV, TOKEN_ASSIGNMENT }; /*expected tokens for error printing purpose*/
	switch (cur_token->kind)
	{
	case TOKEN_MUL:
		print_parser_rule("EXPRESSION_CLEAN -> ar_op EXPRESSION");
		return parse_expression();
		break;
	case TOKEN_DIV:
		print_parser_rule("EXPRESSION_CLEAN -> ar_op EXPRESSION");
		return parse_expression();
		break;
	/*case TOKEN_ASSIGNMENT:
		print_parser_rule("EXPRESSION_CLEAN -> ar_op EXPRESSION");
		parse_expression();
		break;*/
	case TOKEN_SEMICOLON:
		print_parser_rule("EXPRESSION_CLEAN -> VARIABLE_CLEAN");
		cur_token = back_token();
		return parse_variable_clean();
		break;
	case TOKEN_OPEN_SQUER_PAR:
		print_parser_rule("EXPRESSION_CLEAN -> VARIABLE_CLEAN");
		cur_token = back_token();
		return parse_variable_clean();
		break;
	default:
		error_recovery(EXPRESSION_CLEAN, expected, 5); /*print error and try to recover*/
		break;
	}
	return 0;
}
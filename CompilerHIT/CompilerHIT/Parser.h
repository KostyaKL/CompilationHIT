#ifndef Parser_H
#define Parser_H

#include "Token.h"
#include "Table.h"

FILE *parser_report; /*file pointer for parser report*/
Token *cur_token; /*pointer to current token*/

typedef enum eVARIABLE /*enum for each variable in grammar*/
{
	PROGRAM,
	VAR_DEFINITIONS,
	VAR_DEFINITIONS_CLEAN,
	VAR_DEFINITION,
	TYPE,
	VARIABLES_LIST,
	VARIABLES_LIST_CLEAN,
	VARIABLE,
	VARIABLE_CLEAN,
	FUNC_DEFINITIONS,
	FUNC_DEFINITIONS_CLEAN,
	FUNC_DEFINITION,
	RETURNED_TYPE,
	PARAM_DEFINITIONS,
	STATEMENTS,
	STATEMENTS_CLEAN,
	STATEMENT,
	RETURN_STATEMENT_CLEAN,
	ID_STATEMENT_CLEAN,
	BLOCK,
	PARAMETERS_LIST,
	EXPRESSION,
	EXPRESSION_CLEAN
}eVARIABLE;

/*explained in RecursiveDescentParser.c*/
void parser();

void parse_block(table_entry *entry);
elm_type parse_expression();
elm_type parse_expression_clean();
void parse_func_definition();
void parse_func_definitions();
void parse_func_definitions_celan();
void parse_param_definitions(table_entry *entry);
int parse_parameters_list(table_entry *entry_func);
void parse_program();
elm_type parse_returned_type();
int parse_statment(table_entry *entry_func);
int parse_statments_clean(table_entry *entry);
int parse_statments(table_entry *entry);
int *parse_id_statment_clean(table_entry *entry);
int parse_return_statment_clean(table_entry *entry);
elm_type parse_type();
void parse_var_definition(table_entry *entry);
void parse_var_definitions(table_entry *entry);
void parse_var_definitions_clean(table_entry *entry);
int parse_variable(elm_type type, table_entry *entry_func, int param_list, int index);
int parse_variable_clean();
int parse_variables_list(elm_type type, table_entry *entry, int param_list);
int parse_variables_list_clean(elm_type type, table_entry *entry, int param_list, int index);
/*explained in RecursiveDescentParser.c*/

/*explained in ParserUtilityFunctions.c*/
int follow[23][5];

void print_parser_rule(char *rule);
void print_parser_error(eTOKENS *expected, int size);
void error_recovery(eVARIABLE var, eTOKENS *expected, int size);
void match(eTOKENS t);
/*explained in ParserUtilityFunctions.c*/

#endif
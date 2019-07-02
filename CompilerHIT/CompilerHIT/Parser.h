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

void parse_block();
void parse_expression();
void parse_expression_clean();
void parse_func_definition();
void parse_func_definitions();
void parse_func_definitions_celan();
void parse_param_definitions(table_entry *entry);
void parse_parameters_list();
void parse_program();
elm_type parse_returned_type();
void parse_statment();
void parse_statments_clean();
void parse_statments();
void parse_id_statment_clean();
void parse_return_statment_clean();
elm_type parse_type();
void parse_var_definition(table_entry *entry);
void parse_var_definitions(table_entry *entry);
void parse_var_definitions_clean(table_entry *entry);
void parse_variable(elm_type type, table_entry *entry_func);
char *parse_variable_clean();
void parse_variables_list(elm_type type, table_entry *entry);
void parse_variables_list_clean(elm_type type, table_entry *entry);
/*explained in RecursiveDescentParser.c*/

/*explained in ParserUtilityFunctions.c*/
int follow[23][5];

void print_parser_rule(char *rule);
void print_parser_error(eTOKENS *expected, int size);
void error_recovery(eVARIABLE var, eTOKENS *expected, int size);
void match(eTOKENS t);
/*explained in ParserUtilityFunctions.c*/

#endif
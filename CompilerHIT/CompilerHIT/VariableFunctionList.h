#ifndef VariableFunctionList_H
#define VariableFunctionList_H

#include "parse_block.h"
#include "parse_expression.h"
#include "parse_expression_clean.h"
#include "parse_func_definition.h"
#include "parse_func_definitions.h"
#include "parse_func_definitions_celan.h"
#include "parse_param_definitions.h"
#include "parse_parameters_list.h"
#include "parse_program.h"
#include "parse_returned_type.h"
#include "parse_statment.h"
#include "parse_statments_clean.h"
#include "parse_statments.h"
#include "parse_id_statment_clean.h"
#include "parse_return_statment_clean.h"
#include "parse_type.h"
#include "parse_var_definition.h"
#include "parse_var_definitions.h"
#include "parse_var_definitions_clean.h"
#include "parse_variable.h"
#include "parse_variable_clean.h"
#include "parse_variables_list.h"
#include "parse_variables_list_clean.h"

#include <stdio.h>
#include "Token.h"

FILE *parser_report;

typedef enum eVARIABLE
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

int follow[23][5];

void print_parser_rule(char *rule);
void print_parser_error(eTOKENS *expected, int size, Token *actual);
Token *error_recovery(eVARIABLE var, eTOKENS *expected, int size, Token *cur_token);
void match(eVARIABLE var, eTOKENS *t);

#endif

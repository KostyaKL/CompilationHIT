#ifndef VariableFunctionList_H
#define VariableFunctionList_H

#include "parse_block.h"
#include "parse_definitions.h"
#include "parse_expression.h"
#include "parse_expression_clean.h"
#include "parse_func_definition.h"
#include "parse_func_definitions.h"
#include "parse_func_definitions_celan.h"
#include "parse_function_call.h"
#include "parse_param_definitions.h"
#include "parse_parameters_list.h"
#include "parse_program.h"
#include "parse_returned_type.h"
#include "parse_statment.h"
#include "parse_statment_clean.h"
#include "parse_statments.h"
#include "parse_type.h"
#include "parse_var_definition.h"
#include "parse_var_definitions.h"
#include "parse_variable.h"
#include "parse_variable_clean.h"
#include "parse_variable_list.h"
#include "parse_variable_list_clean.h"

#include <stdio.h>
#include "Token.h"

FILE *parser_report;

void print_parser_rule(char *rule);
void print_parser_error(eTOKENS expected, Token *actual);

#endif

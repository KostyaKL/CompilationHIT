#include "VariableFunctionList.h"
#include "Token.h"

void parse_var_definition() {
	Token *cur_token = next_token();
	switch (cur_token->kind)
	{
	case TOKEN_REAL:
		print_parser_rule("VAR_DEFINITION -> TYPE VARIABLES_LIST");
		parse_type();
		parse_variable_list();
		break;
	case TOKEN_INTEGER:
		print_parser_rule("VAR_DEFINITION -> TYPE VARIABLES_LIST");
		parse_type();
		parse_variable_list();
		break;
	default:
		error_recovery(TOKEN_REAL, cur_token);
		break;
	}
}
#include "VariableFunctionList.h"

#define NUM_OF_EXPECTED 2

void parse_var_definition() {
	Token *cur_token = next_token();
	eTOKENS expected[NUM_OF_EXPECTED] = { TOKEN_REAL, TOKEN_INTEGER };
	switch (cur_token->kind)
	{
	case TOKEN_REAL:
		print_parser_rule("VAR_DEFINITION -> TYPE VARIABLES_LIST");
		parse_type();
		parse_variables_list();
		break;
	case TOKEN_INTEGER:
		print_parser_rule("VAR_DEFINITION -> TYPE VARIABLES_LIST");
		parse_type();
		parse_variables_list();
		break;
	default:
		error_recovery(VAR_DEFINITION, expected, NUM_OF_EXPECTED, cur_token);
		break;
	}
}
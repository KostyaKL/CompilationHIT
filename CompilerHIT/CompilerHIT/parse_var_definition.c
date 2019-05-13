#include "VariableFunctionList.h"
#include "Token.h"

void parse_var_definition() {
	Token *cur_token = next_token();
	eTOKENS expected[2] = { TOKEN_REAL, TOKEN_INTEGER };
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
		error_recovery(VAR_DEFINITION, expected, 2, cur_token);
		break;
	}
}
#include "VariableFunctionList.h"

#define NUM_OF_EXPECTED 3

void parse_param_definitions() {
	Token *cur_token = next_token();
	eTOKENS expected[NUM_OF_EXPECTED] = { TOKEN_REAL, TOKEN_INTEGER, TOKEN_EOF };
	switch (cur_token->kind)
	{
	case TOKEN_REAL:
		print_parser_rule("PARAM_DEFINITIONS -> VAR_DEFINITIONS");
		parse_var_definitions();
		break;
	case TOKEN_INTEGER:
		print_parser_rule("PARAM_DEFINITIONS -> VAR_DEFINITIONS");
		parse_var_definitions();
		break;
	case TOKEN_EOF:
		print_parser_rule("PARAM_DEFINITIONS -> epsilon");
		back_token();
		break;
	default:
		error_recovery(PARAM_DEFINITIONS, expected, NUM_OF_EXPECTED, cur_token);
		break;
	}
}
#include "VariableFunctionList.h"

#define NUM_OF_EXPECTED 3

void parse_param_definitions() {
	cur_token = next_token();
	eTOKENS expected[NUM_OF_EXPECTED] = { TOKEN_REAL, TOKEN_INTEGER, TOKEN_CLOSE_CIRCULAR_PAR };
	switch (cur_token->kind)
	{
	case TOKEN_REAL:
		print_parser_rule("PARAM_DEFINITIONS -> VAR_DEFINITIONS");
		cur_token = back_token();
		parse_var_definitions();
		break;
	case TOKEN_INTEGER:
		print_parser_rule("PARAM_DEFINITIONS -> VAR_DEFINITIONS");
		cur_token = back_token();
		parse_var_definitions();
		break;
	case TOKEN_CLOSE_CIRCULAR_PAR:
		print_parser_rule("PARAM_DEFINITIONS -> epsilon");
		//cur_token = back_token();
		break;
	default:
		error_recovery(PARAM_DEFINITIONS, expected, NUM_OF_EXPECTED, cur_token);
		break;
	}
}
#include "VariableFunctionList.h"

#define NUM_OF_EXPECTED 2

void parse_var_definitions() {
	Token *cur_token = next_token();
	eTOKENS expected[NUM_OF_EXPECTED] = { TOKEN_REAL, TOKEN_INTEGER };
	switch (cur_token->kind)
	{
	case TOKEN_REAL:
		print_parser_rule(" VAR_DEFINITIONS -> VAR_DEFINITION VAR_DEFINITIONS_CLEAN");
		back_token();
		parse_var_definition();
		back_token();
		parse_var_definitions_clean();
		break;
	case TOKEN_INTEGER:
		print_parser_rule(" VAR_DEFINITIONS -> VAR_DEFINITION VAR_DEFINITIONS_CLEAN");
		back_token();
		parse_var_definition();
		back_token();
		parse_var_definitions_clean();
		break;
	default:
		error_recovery(VAR_DEFINITIONS, expected, NUM_OF_EXPECTED, cur_token);
		break;
	}
}
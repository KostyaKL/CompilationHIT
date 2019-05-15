#include "VariableFunctionList.h"

#define NUM_OF_EXPECTED 1

void parse_program() {
	cur_token = next_token();
	eTOKENS expected[NUM_OF_EXPECTED] = { TOKEN_PROGRAM };
	switch (cur_token->kind)
	{
	case TOKEN_PROGRAM:
		print_parser_rule("PROGRAM -> program VAR_DEFINITIONS ; STATMENTS end FUNC_DEFINITIONS");
		parse_var_definitions();
		match(TOKEN_SEMICOLON);
		parse_statments();
		match(TOKEN_END);
		parse_func_definitions();
		break;
	default:
		error_recovery(PROGRAM, expected, NUM_OF_EXPECTED);
		break;
	}
}
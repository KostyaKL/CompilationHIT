#include "VariableFunctionList.h"

#define NUM_OF_EXPECTED 1

void parse_program() {
	cur_token = next_token();
	eTOKENS expected[NUM_OF_EXPECTED] = { TOKEN_PROGRAM };
	switch (cur_token->kind)
	{
	case TOKEN_PROGRAM:
		print_parser_rule("PROGRAM -> program VAR_DEFINITIONS ; STATMENTS end FUNC_DEFINITIONS");
		//cur_token = back_token();
		parse_var_definitions();
		match(TOKEN_SEMICOLON);
		cur_token = back_token();
		parse_statments();
		match(TOKEN_END);
		cur_token = back_token();
		parse_func_definitions();
		break;
	default:
		error_recovery(PROGRAM, expected, NUM_OF_EXPECTED);
		break;
	}
}
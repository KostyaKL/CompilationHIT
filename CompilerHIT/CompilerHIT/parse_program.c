#include "VariableFunctionList.h"

#define NUM_OF_EXPECTED 1

void parse_program() {
	Token *cur_token = next_token();
	eTOKENS expected[NUM_OF_EXPECTED] = { TOKEN_PROGRAM };
	switch (cur_token->kind)
	{
	case TOKEN_PROGRAM:
		print_parser_rule("PROGRAM -> program VAR_DEFINITIONS ; STATMENTS end FUNC_DEFINITIONS");
		back_token();
		parse_var_definitions();
		match(TOKEN_SEMICOLON);
		back_token();
		parse_statments();
		match(TOKEN_END);
		back_token();
		parse_func_definitions();
		break;
	default:
		error_recovery(PROGRAM, expected, NUM_OF_EXPECTED, cur_token);
		break;
	}
}
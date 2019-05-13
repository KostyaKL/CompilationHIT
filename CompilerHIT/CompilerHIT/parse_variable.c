#include "VariableFunctionList.h"
#include "Token.h"

#define NUM_OF_EXPECTED 1

void parse_variable() {
	Token *cur_token = next_token();
	eTOKENS expected[NUM_OF_EXPECTED] = { TOKEN_ID };
	switch (cur_token->kind)
	{
	case TOKEN_ID:
		print_parser_rule("VARIABLE -> id VARIABLE_CLEAN");
		parse_variable_clean();
		break;
	default:
		error_recovery(VARIABLE, expected, NUM_OF_EXPECTED, cur_token);
		break;
	}
}
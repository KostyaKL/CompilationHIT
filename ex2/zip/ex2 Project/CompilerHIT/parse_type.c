#include "VariableFunctionList.h"

#define NUM_OF_EXPECTED 2

void parse_type() {
	cur_token = next_token();
	eTOKENS expected[NUM_OF_EXPECTED] = { TOKEN_REAL, TOKEN_INTEGER };
	switch (cur_token->kind)
	{
	case TOKEN_REAL:
		print_parser_rule("TYPE -> real");
		break;
	case TOKEN_INTEGER:
		print_parser_rule("TYPE -> integer");
		break;
	default:
		error_recovery(TYPE, expected, NUM_OF_EXPECTED);
		break;
	}
}
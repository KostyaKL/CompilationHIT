#include "VariableFunctionList.h"

#define NUM_OF_EXPECTED 3

void parse_returned_type() {
	cur_token = next_token();
	eTOKENS expected[NUM_OF_EXPECTED] = { TOKEN_REAL, TOKEN_INTEGER, TOKEN_VOID };
	switch (cur_token->kind)
	{
	case TOKEN_REAL:
		print_parser_rule("RETURNED_TYPE -> TYPE");
		cur_token = back_token();
		parse_type();
		break;
	case TOKEN_INTEGER:
		print_parser_rule("RETURNED_TYPE -> TYPE");
		cur_token = back_token();
		parse_type();
		break;
	case TOKEN_VOID:
		print_parser_rule("RETURNED_TYPE -> void");
		break;
	default:
		error_recovery(RETURNED_TYPE, expected, NUM_OF_EXPECTED);
		break;
	}
}
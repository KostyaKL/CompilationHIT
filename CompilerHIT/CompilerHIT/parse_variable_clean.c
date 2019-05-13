#include "VariableFunctionList.h"
#include "Token.h"

#define NUM_OF_EXPECTED 2

void parse_variable_clean() {
	Token *cur_token = next_token();
	eTOKENS expected[NUM_OF_EXPECTED] = { TOKEN_OPEN_SQUER_PAR, TOKEN_EOF };
	switch (cur_token->kind)
	{
	case TOKEN_OPEN_SQUER_PAR:
		print_parser_rule("VARIABLE_CLEAN -> [ int_number ]");
		match(VARIABLE_CLEAN, TOKEN_INT_NUMBER);
		match(VARIABLE_CLEAN, TOKEN_CLOSE_SQUER_PAR);
		break;
	case TOKEN_EOF:
		print_parser_rule("VARIABLE_CLEAN -> epsilon");
		break;
	default:
		error_recovery(VARIABLE_CLEAN, expected, NUM_OF_EXPECTED, cur_token);
		break;
	}
}
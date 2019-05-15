#include "VariableFunctionList.h"

#define NUM_OF_EXPECTED 2

void parse_var_definitions_clean() {
	next_token();
	Token *peek = next_token();
	eTOKENS expected[NUM_OF_EXPECTED] = { TOKEN_SEMICOLON, TOKEN_CLOSE_CIRCULAR_PAR };
	cur_token = back_token();
	switch (cur_token->kind)
	{
	case TOKEN_SEMICOLON:
		if (peek->kind == TOKEN_REAL || peek->kind == TOKEN_INTEGER) {
			print_parser_rule("VAR_DEFINITIONS_CLEAN -> ; VAR_DEFINITIONS");
			parse_var_definitions();
		}
		else {
			print_parser_rule("VAR_DEFINITIONS_CLEAN -> epsilon");
			cur_token = back_token();
		}
		break;
	case TOKEN_CLOSE_CIRCULAR_PAR:
		print_parser_rule("VAR_DEFINITIONS_CLEAN -> epsilon");
		cur_token = back_token();
		break;
	default:
		error_recovery(VAR_DEFINITIONS_CLEAN, expected, NUM_OF_EXPECTED);
		break;
	}
}
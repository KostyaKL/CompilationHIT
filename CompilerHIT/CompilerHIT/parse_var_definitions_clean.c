#include "VariableFunctionList.h"

#define NUM_OF_EXPECTED 1

void parse_var_definitions_clean() {
	Token *cur_token = next_token();
	Token *peek = next_token();
	eTOKENS expected[NUM_OF_EXPECTED] = { TOKEN_SEMICOLON };
	back_token();
	switch (cur_token->kind)
	{
	case TOKEN_SEMICOLON:
		if (peek->kind == TOKEN_EOF) {
			print_parser_rule("VAR_DEFINITIONS_CLEAN -> epsilon");
			back_token();
		}
		else {
			print_parser_rule("VAR_DEFINITIONS_CLEAN -> ; VAR_DEFINITIONS");
			back_token();
			parse_var_definitions();
		}
		break;
	default:
		error_recovery(VAR_DEFINITIONS_CLEAN, expected, NUM_OF_EXPECTED, cur_token);
		break;
	}
}
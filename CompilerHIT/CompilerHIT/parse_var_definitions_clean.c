#include "VariableFunctionList.h"
#include "Token.h"

#define NUM_OF_EXPECTED 2

void parse_var_definitions_clean() {
	Token *cur_token = next_token();
	eTOKENS expected[NUM_OF_EXPECTED] = { TOKEN_SEMICOLON, TOKEN_EOF };
	switch (cur_token->kind)
	{
	case TOKEN_SEMICOLON:
		print_parser_rule("VAR_DEFINITIONS_CLEAN -> ; VAR_DEFINITIONS");
		match(VAR_DEFINITIONS_CLEAN, TOKEN_SEMICOLON);
		parse_var_definitions();
		break;
	case TOKEN_EOF:
		print_parser_rule("VAR_DEFINITIONS_CLEAN -> epsilon");
		break;
	default:
		error_recovery(VAR_DEFINITIONS_CLEAN, expected, NUM_OF_EXPECTED, cur_token);
		break;
	}
}
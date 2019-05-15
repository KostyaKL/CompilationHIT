#include "VariableFunctionList.h"

#define NUM_OF_EXPECTED 1

void parse_block() {
	Token *cur_token = next_token();
	eTOKENS expected[NUM_OF_EXPECTED] = { TOKEN_OPEN_CURLY_PAR };
	switch (cur_token->kind)
	{
	case TOKEN_OPEN_CURLY_PAR:
		print_parser_rule("BLOCK -> { VAR_DEFINITIONS ; STATMENTS }");
		back_token();
		parse_var_definitions();
		match(TOKEN_SEMICOLON);
		back_token();
		parse_statments();
		match(TOKEN_CLOSE_CURLY_PAR);
		break;
	default:
		error_recovery(BLOCK, expected, NUM_OF_EXPECTED, cur_token);
		break;
	} 
}
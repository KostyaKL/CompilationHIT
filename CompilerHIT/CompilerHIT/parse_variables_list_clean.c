#include "VariableFunctionList.h"
#include "Token.h"

#define NUM_OF_EXPECTED 2

void parse_variables_list_clean() {
	Token *cur_token = next_token();
	eTOKENS expected[NUM_OF_EXPECTED] = { TOKEN_COMMA, TOKEN_EOF };
	switch (cur_token->kind)
	{
	case TOKEN_COMMA: 
		print_parser_rule("VARIABLES_LIST_CLEAN -> , VARIABLE VARIABLES_LIST_CLEAN");
		parse_variable();
		parse_variables_list_clean();
		break;
	case TOKEN_EOF:
		print_parser_rule("VARIABLES_LIST_CLEAN -> epsilon");
		back_token();
		break;
	default:
		error_recovery(VARIABLES_LIST_CLEAN, expected, NUM_OF_EXPECTED, cur_token);
		break;
	}
}
#include "VariableFunctionList.h"

#define NUM_OF_EXPECTED 1

void parse_variables_list() {
	Token *cur_token = next_token();
	eTOKENS expected[NUM_OF_EXPECTED] = { TOKEN_ID };
	switch (cur_token->kind)
	{
	case TOKEN_ID: 
		print_parser_rule("VARIABLES_LIST -> VARIABLE VARIABLES_LIST_CLEAN");
		back_token();
		parse_variable();
		back_token();
		parse_variables_list_clean();
		break;
	default:
		error_recovery(VARIABLES_LIST, expected, NUM_OF_EXPECTED, cur_token);
		break;
	}
}
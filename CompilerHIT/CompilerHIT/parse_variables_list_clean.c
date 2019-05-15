#include "VariableFunctionList.h"

#define NUM_OF_EXPECTED 3

void parse_variables_list_clean() {
	cur_token = next_token();
	eTOKENS expected[NUM_OF_EXPECTED] = { TOKEN_COMMA, TOKEN_SEMICOLON, TOKEN_CLOSE_CIRCULAR_PAR };
	switch (cur_token->kind)
	{
	case TOKEN_COMMA: 
		print_parser_rule("VARIABLES_LIST_CLEAN -> , VARIABLE VARIABLES_LIST_CLEAN");
		//cur_token = back_token();
		parse_variable();
		cur_token = back_token();
		parse_variables_list_clean();
		break;
	case TOKEN_SEMICOLON:
		print_parser_rule("VARIABLES_LIST_CLEAN -> epsilon");
		//cur_token = back_token();
		break;
	case TOKEN_CLOSE_CIRCULAR_PAR:
		print_parser_rule("VARIABLES_LIST_CLEAN -> epsilon");
		//cur_token = back_token();
		break;
	default:
		error_recovery(VARIABLES_LIST_CLEAN, expected, NUM_OF_EXPECTED);
		break;
	}
}
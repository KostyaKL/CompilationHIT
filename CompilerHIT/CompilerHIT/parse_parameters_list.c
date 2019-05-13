#include "VariableFunctionList.h"
#include "Token.h"

#define NUM_OF_EXPECTED 2

void parse_parameters_list() {
	Token *cur_token = next_token();
	eTOKENS expected[NUM_OF_EXPECTED] = { TOKEN_ID, TOKEN_EOF };
	switch (cur_token->kind)
	{
	case TOKEN_ID: 
		print_parser_rule("PARAMETERS_LIST -> VARIABLES_LIST");
		parse_variables_list();
		break;
	case TOKEN_EOF:
		print_parser_rule("PARAMETERS_LIST -> epsilon");
		back_token();
		break;
	default:
		error_recovery(PARAMETERS_LIST, expected, NUM_OF_EXPECTED, cur_token);
		break;
	}
}
#include "VariableFunctionList.h"
#include "Token.h"

#define NUM_OF_EXPECTED 3

void parse_expression() {
	Token *cur_token = next_token();
	eTOKENS expected[NUM_OF_EXPECTED] = { TOKEN_ID, TOKEN_INT_NUMBER, TOKEN_REAL_NUMBER };
	switch (cur_token->kind)
	{
	case TOKEN_ID: 
		print_parser_rule("EXPRESSION -> id EXPRESSION_CLEAN");
		parse_expression_clean();
		break;
	case TOKEN_INT_NUMBER:
		print_parser_rule("EXPRESSION -> id int_number");
		break;
	case TOKEN_REAL_NUMBER:
		print_parser_rule("EXPRESSION -> id real_number");
		break;
	default:
		error_recovery(EXPRESSION, expected, NUM_OF_EXPECTED, cur_token);
		break;
	}
}
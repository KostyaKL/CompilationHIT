#include "VariableFunctionList.h"
#include "Token.h"

#define NUM_OF_EXPECTED 4

void parse_return_statment_clean() {
	Token *cur_token = next_token();
	eTOKENS expected[NUM_OF_EXPECTED] = { TOKEN_ID, TOKEN_INT_NUMBER, TOKEN_REAL_NUMBER, TOKEN_EOF };
	switch (cur_token->kind)
	{
	case TOKEN_ID: 
		print_parser_rule("RETURN_STATEMENT_CLEAN -> EXPRESSION");
		parse_expression();
		break;
	case TOKEN_INT_NUMBER:
		print_parser_rule("RETURN_STATEMENT_CLEAN -> EXPRESSION");
		parse_expression();
		break;
	case TOKEN_REAL_NUMBER:
		print_parser_rule("RETURN_STATEMENT_CLEAN -> EXPRESSION");
		parse_expression();
		break;
	case TOKEN_EOF:
		print_parser_rule("RETURN_STATEMENT_CLEAN -> epsilon");
		break;
	default:
		error_recovery(RETURN_STATEMENT_CLEAN, expected, NUM_OF_EXPECTED, cur_token);
		break;
	}
}
#include "VariableFunctionList.h"
#include "Token.h"

#define NUM_OF_EXPECTED 4

void parse_statments_clean() {
	Token *cur_token = next_token();
	eTOKENS expected[NUM_OF_EXPECTED] = { TOKEN_ID, TOKEN_RETURN, TOKEN_OPEN_CURLY_PAR, TOKEN_EOF };
	switch (cur_token->kind)
	{
	case TOKEN_ID:
		print_parser_rule("STATEMENTS_CLEAN -> STATMENTS");
		parse_statments();
		break;
	case TOKEN_RETURN:
		print_parser_rule("STATEMENTS_CLEAN -> STATMENTS");
		parse_statments();
		break;
	case TOKEN_OPEN_CURLY_PAR:
		print_parser_rule("STATEMENTS_CLEAN -> STATMENTS");
		parse_statments();
		break;
	case TOKEN_EOF:
		print_parser_rule("STATEMENTS_CLEAN -> epsilon");
		back_token();
		break;
	default:
		error_recovery(STATEMENTS_CLEAN, expected, NUM_OF_EXPECTED, cur_token);
		break;
	}
}
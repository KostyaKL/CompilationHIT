#include "VariableFunctionList.h"

#define NUM_OF_EXPECTED 5

void parse_statments_clean() {
	cur_token = next_token();
	eTOKENS expected[NUM_OF_EXPECTED] = { TOKEN_ID, TOKEN_RETURN, TOKEN_OPEN_CURLY_PAR, TOKEN_END, TOKEN_CLOSE_CURLY_PAR };
	switch (cur_token->kind)
	{
	case TOKEN_ID:
		print_parser_rule("STATEMENTS_CLEAN -> STATMENTS");
		cur_token = back_token();
		parse_statments();
		break;
	case TOKEN_RETURN:
		print_parser_rule("STATEMENTS_CLEAN -> STATMENTS");
		cur_token = back_token();
		parse_statments();
		break;
	case TOKEN_OPEN_CURLY_PAR:
		print_parser_rule("STATEMENTS_CLEAN -> STATMENTS");
		cur_token = back_token();
		parse_statments();
		break;
	case TOKEN_END:
		print_parser_rule("STATEMENTS_CLEAN -> epsilon");
		//cur_token = back_token();
		break;
	case TOKEN_CLOSE_CURLY_PAR:
		print_parser_rule("STATEMENTS_CLEAN -> epsilon");
		//cur_token = back_token();
		break;
	default:
		error_recovery(STATEMENTS_CLEAN, expected, NUM_OF_EXPECTED, cur_token);
		break;
	}
}
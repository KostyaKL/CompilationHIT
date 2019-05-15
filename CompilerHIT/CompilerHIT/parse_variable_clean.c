#include "VariableFunctionList.h"

#define NUM_OF_EXPECTED 5

void parse_variable_clean() {
	cur_token = next_token();
	eTOKENS expected[NUM_OF_EXPECTED] = { TOKEN_OPEN_SQUER_PAR, TOKEN_ASSIGNMENT, TOKEN_COMMA, TOKEN_SEMICOLON, TOKEN_CLOSE_CIRCULAR_PAR };
	switch (cur_token->kind)
	{
	case TOKEN_OPEN_SQUER_PAR:
		print_parser_rule("VARIABLE_CLEAN -> [ int_number ]");
		match(TOKEN_INT_NUMBER);
		match(TOKEN_CLOSE_SQUER_PAR);
		//cur_token = next_token();
		break;
	case TOKEN_ASSIGNMENT:
		print_parser_rule("VARIABLE_CLEAN -> epsilon");
		cur_token = back_token();
		break;
	case TOKEN_COMMA:
		print_parser_rule("VARIABLE_CLEAN -> epsilon");
		cur_token = back_token();
		break;
	case TOKEN_SEMICOLON:
		print_parser_rule("VARIABLE_CLEAN -> epsilon");
		cur_token = back_token();
		break;
	case TOKEN_CLOSE_CIRCULAR_PAR:
		print_parser_rule("VARIABLE_CLEAN -> epsilon");
		cur_token = back_token();
		break;
	default:
		error_recovery(VARIABLE_CLEAN, expected, NUM_OF_EXPECTED);
		break;
	}
}
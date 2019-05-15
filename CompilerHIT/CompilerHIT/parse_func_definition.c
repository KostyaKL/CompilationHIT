#include "VariableFunctionList.h"

#define NUM_OF_EXPECTED 3

void parse_func_definition() {
	cur_token = next_token();
	eTOKENS expected[NUM_OF_EXPECTED] = { TOKEN_REAL, TOKEN_INTEGER, TOKEN_VOID };
	switch (cur_token->kind)
	{
	case TOKEN_REAL:
		print_parser_rule("FUNC_DEFINITION -> RETURNED_TYPE id ( PARAM_DEFINITIONS ) BLOCK");
		cur_token = back_token();
		parse_returned_type();
		match(TOKEN_ID);
		match(TOKEN_OPEN_CIRCULAR_PAR);
		cur_token = back_token();
		parse_param_definitions();
		match(TOKEN_CLOSE_CIRCULAR_PAR);
		cur_token = back_token();
		parse_block();
		break;
	case TOKEN_INTEGER:
		print_parser_rule("FUNC_DEFINITION -> RETURNED_TYPE id ( PARAM_DEFINITIONS ) BLOCK");
		cur_token = back_token();
		parse_returned_type();
		match(TOKEN_ID);
		match(TOKEN_OPEN_CIRCULAR_PAR);
		cur_token = back_token();
		parse_param_definitions();
		match(TOKEN_CLOSE_CIRCULAR_PAR);
		cur_token = back_token();
		parse_block();
		break;
	case TOKEN_VOID:
		print_parser_rule("FUNC_DEFINITION -> RETURNED_TYPE id ( PARAM_DEFINITIONS ) BLOCK");
		cur_token = back_token();
		parse_returned_type();
		match(TOKEN_ID);
		match(TOKEN_OPEN_CIRCULAR_PAR);
		cur_token = back_token();
		parse_param_definitions();
		match(TOKEN_CLOSE_CIRCULAR_PAR);
		cur_token = back_token();
		parse_block();
		break;
	default:
		error_recovery(FUNC_DEFINITION, expected, NUM_OF_EXPECTED, cur_token);
		break;
	}
}
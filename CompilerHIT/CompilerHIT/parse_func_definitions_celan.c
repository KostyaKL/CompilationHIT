#include "VariableFunctionList.h"

#define NUM_OF_EXPECTED 4

void parse_func_definitions_celan() {
	cur_token = next_token();
	eTOKENS expected[NUM_OF_EXPECTED] = { TOKEN_REAL, TOKEN_INTEGER, TOKEN_VOID, TOKEN_EOF };
	switch (cur_token->kind)
	{
	case TOKEN_REAL:
		print_parser_rule("FUNC_DEFINITIONS_CLEAN -> FUNC_DEFINITION FUNC_DEFINITIONS_CLEAN");
		cur_token = back_token();
		parse_func_definition();
		cur_token = back_token();
		parse_func_definitions_celan();
		break;
	case TOKEN_INTEGER:
		print_parser_rule("FUNC_DEFINITIONS_CLEAN -> FUNC_DEFINITION FUNC_DEFINITIONS_CLEAN");
		cur_token = back_token();
		parse_func_definition();
		cur_token = back_token();
		parse_func_definitions_celan();
		break;
	case TOKEN_VOID:
		print_parser_rule("FUNC_DEFINITIONS_CLEAN -> FUNC_DEFINITION FUNC_DEFINITIONS_CLEAN");
		cur_token = back_token();
		parse_func_definition();
		cur_token = back_token();
		parse_func_definitions_celan();
		break;
	case TOKEN_EOF:
		print_parser_rule("FUNC_DEFINITIONS_CLEAN -> epsilon");
		//cur_token = back_token();
		break;
	default:
		error_recovery(FUNC_DEFINITIONS_CLEAN, expected, NUM_OF_EXPECTED, cur_token);
		break;
	}
}
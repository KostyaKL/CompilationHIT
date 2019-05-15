#include "VariableFunctionList.h"

#define NUM_OF_EXPECTED 3

void parse_func_definitions() {
	cur_token = next_token();
	eTOKENS expected[NUM_OF_EXPECTED] = { TOKEN_REAL, TOKEN_INTEGER, TOKEN_VOID };
	switch (cur_token->kind)
	{
	case TOKEN_REAL: 
		print_parser_rule("FUNC_DEFINITIONS -> FUNC_DEFINITION FUNC_DEFINITIONS_CLEAN");
		cur_token = back_token();
		parse_func_definition();
		parse_func_definitions_celan();
		break;
	case TOKEN_INTEGER:
		print_parser_rule("FUNC_DEFINITIONS -> FUNC_DEFINITION FUNC_DEFINITIONS_CLEAN");
		cur_token = back_token();
		parse_func_definition();
		parse_func_definitions_celan();
		break;
	case TOKEN_VOID:
		print_parser_rule("FUNC_DEFINITIONS -> FUNC_DEFINITION FUNC_DEFINITIONS_CLEAN");
		cur_token = back_token();
		parse_func_definition();
		parse_func_definitions_celan();
		break;
	default:
		error_recovery(FUNC_DEFINITIONS, expected, NUM_OF_EXPECTED);
		break;
	}
}
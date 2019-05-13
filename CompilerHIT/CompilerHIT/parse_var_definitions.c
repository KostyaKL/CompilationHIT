#include "VariableFunctionList.h"
#include "Token.h"

void parse_var_definitions() {
	Token *cur_token = next_token();
	eTOKENS expected[2] = { TOKEN_REAL, TOKEN_INTEGER };
	switch (cur_token->kind)
	{
	case TOKEN_REAL:
		print_parser_rule(" VAR_DEFINITIONS -> VAR_DEFINITION VAR_DEFINITIONS_CLEAN");
		parse_var_definition();
		parse_var_definitions_clean();
		break;
	case TOKEN_INTEGER:
		print_parser_rule(" VAR_DEFINITIONS -> VAR_DEFINITION VAR_DEFINITIONS_CLEAN");
		parse_var_definition();
		parse_var_definitions_clean();
		break;
	default:
		error_recovery(VAR_DEFINITIONS, expected, 2, cur_token);
		break;
	}
}
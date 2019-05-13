#include "VariableFunctionList.h"
#include "Token.h"

void parse_var_definitions_clean() {
	Token *cur_token = next_token();
	switch (cur_token->kind)
	{
	case TOKEN_SEMICOLON:
		print_parser_rule("VAR_DEFINITIONS_CLEAN -> ; VAR_DEFINITIONS");
		match(TOKEN_SEMICOLON);
		parse_var_definitions();
		break;
	case TOKEN_EOF:
		print_parser_rule("VAR_DEFINITIONS_CLEAN -> epsilon");
		break;
	default:
		error_recovery(TOKEN_SEMICOLON, cur_token);
		break;
	}
}
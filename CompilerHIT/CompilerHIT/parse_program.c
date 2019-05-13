#include "VariableFunctionList.h"
#include "Token.h"

void parse_program() {
	Token *cur_token = next_token();
	switch (cur_token->kind)
	{
	case TOKEN_PROGRAM:
		print_parser_rule("PROGRAM -> program VAR_DEFINITIONS; STATMENTS end FUNC_DEFINITIONS");
		parse_var_definitions();
		match(TOKEN_SEMICOLON);
		parse_statments();
		match(TOKEN_END);
		parse_func_definitions();
		break;
	default:
		error_recovery(TOKEN_PROGRAM, cur_token);
		break;
	}
}
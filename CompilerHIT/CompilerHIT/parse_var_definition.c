#include "parse_var_definition.h"
#include "Token.h"

void parse_var_definition() {
	Token *cur_token = next_token();
	switch (cur_token->kind)
	{
	case TOKEN:
		print;
		match();
		break;
	default:
		error;
		break;
	}

}
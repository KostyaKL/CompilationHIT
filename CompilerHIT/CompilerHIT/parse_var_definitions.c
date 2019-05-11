#include "parse_var_definitions.h"
#include "Token.h"

void parse_var_definitions() {
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
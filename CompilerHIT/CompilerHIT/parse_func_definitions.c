#include "parse_func_definitions.h"
#include "Token.h"

void parse_func_definitions() {
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
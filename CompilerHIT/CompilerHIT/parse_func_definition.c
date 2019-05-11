#include "parse_func_definition.h"
#include "Token.h"

void parse_func_definition() {
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
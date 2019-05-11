#include "parse_param_definitions.h"
#include "Token.h"

void parse_param_definitions() {
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
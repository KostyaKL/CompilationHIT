#include "parse_func_definitions_celan.h"
#include "Token.h"

void parse_func_definitions_celan() {
	Token *cur_token = next_token();
	switch (cur_token->kind)
	{
	case TOKEN_EOF:
		//print;
		match(TOKEN_EOF);
		break;
	default:
		//error;
		break;
	}

}
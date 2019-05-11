#include "parse_var_definition.h"
#include "Token.h"

void parse_var_definition() {
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
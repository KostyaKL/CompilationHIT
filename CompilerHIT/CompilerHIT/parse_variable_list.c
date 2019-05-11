#include "parse_variable_list.h"
#include "Token.h"

void parse_variable_list() {
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
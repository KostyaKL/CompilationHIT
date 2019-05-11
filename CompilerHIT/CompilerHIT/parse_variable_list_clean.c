#include "parse_variable_list_clean.h"
#include "Token.h"

void parse_variable_list_clean() {
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
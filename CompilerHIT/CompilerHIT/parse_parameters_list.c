#include "parse_parameters_list.h"
#include "Token.h"

void parse_parameters_list() {
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
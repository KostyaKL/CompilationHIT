#include "parse_returned_type.h"
#include "Token.h"

void parse_returned_type() {
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
#include "parse_expression_clean.h"
#include "Token.h"

void parse_expression_clean() {
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
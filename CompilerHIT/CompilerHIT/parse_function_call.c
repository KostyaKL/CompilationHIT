#include "parse_function_call.h"
#include "Token.h"

void parse_function_call() {
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
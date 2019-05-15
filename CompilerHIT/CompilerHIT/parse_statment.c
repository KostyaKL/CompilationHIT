#include "VariableFunctionList.h"

#define NUM_OF_EXPECTED 3

void parse_statment() {
	cur_token = next_token();
	eTOKENS expected[NUM_OF_EXPECTED] = { TOKEN_ID, TOKEN_RETURN, TOKEN_OPEN_CURLY_PAR };
	switch (cur_token->kind)
	{
	case TOKEN_ID: 
		print_parser_rule("STATEMENT -> id ID_STATEMENT_CLEAN");
		//cur_token = back_token();
		parse_id_statment_clean();
		break;
	case TOKEN_RETURN: 
		print_parser_rule("STATEMENT -> return ID_STATEMENT_CLEAN");
		//cur_token = back_token();
		parse_id_statment_clean();
		break;
	case TOKEN_OPEN_CURLY_PAR:
		print_parser_rule("STATEMENT -> BLOCK");
		cur_token = back_token();
		parse_block();
		break;
	default:
		error_recovery(STATEMENT, expected, NUM_OF_EXPECTED, cur_token);
		break;
	}
}
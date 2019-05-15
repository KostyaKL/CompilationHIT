#include "VariableFunctionList.h"

#define NUM_OF_EXPECTED 2

void parse_id_statment_clean() {
	cur_token = next_token();
	eTOKENS expected[NUM_OF_EXPECTED] = { TOKEN_OPEN_SQUER_PAR, TOKEN_OPEN_CIRCULAR_PAR };
	switch (cur_token->kind)
	{
	case TOKEN_OPEN_SQUER_PAR:
		print_parser_rule("ID_STATEMENT_CLEAN -> VARIABLE_CLEAN = EXPRESSION");
		cur_token = back_token();
		parse_variable_clean();
		match(TOKEN_ASSIGNMENT);
		parse_expression();
		break;
	case TOKEN_OPEN_CIRCULAR_PAR: 
		print_parser_rule("ID_STATEMENT_CLEAN -> ( PARAMETERS_LIST )");
		//cur_token = back_token();
		parse_parameters_list();
		match(TOKEN_CLOSE_CIRCULAR_PAR);
		break;
	default:
		error_recovery(ID_STATEMENT_CLEAN, expected, NUM_OF_EXPECTED, cur_token);
		break;
	}
}
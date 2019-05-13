#include "VariableFunctionList.h"
#include "Token.h"

const char* getTokenName(eTOKENS token)
{
	switch (token)
	{
	case TOKEN_PROGRAM: return "TOKEN_PROGRAM";
	case TOKEN_END: return "TOKEN_END";
	case TOKEN_REAL: return "TOKEN_REAL";
	case TOKEN_INTEGER: return "TOKEN_INTEGER";
	case TOKEN_VOID: return "TOKEN_VOID";
	case TOKEN_RETURN: return "TOKEN_RETURN";
	case TOKEN_MUL: return "TOKEN_MUL";
	case TOKEN_DIV: return "TOKEN_DIV";
	case TOKEN_ASSIGNMENT: return "TOKEN_ASSIGNMENT";
	case TOKEN_COMMA: return "TOKEN_COMMA";
	case TOKEN_SEMICOLON: return "TOKEN_SEMICOLON";
	case TOKEN_OPEN_CIRCULAR_PAR: return "TOKEN_OPEN_CIRCULAR_PAR";
	case TOKEN_CLOSE_CIRCULAR_PAR: return "TOKEN_CLOSE_CIRCULAR_PAR";
	case TOKEN_OPEN_SQUER_PAR: return "TOKEN_OPEN_SQUER_PAR";
	case TOKEN_CLOSE_SQUER_PAR: return "TOKEN_CLOSE_SQUER_PAR";
	case TOKEN_OPEN_CURLY_PAR: return "TOKEN_OPEN_CURLY_PAR";
	case TOKEN_CLOSE_CURLY_PAR: return "TOKEN_CLOSE_CURLY_PAR";
	case TOKEN_COMMENT: return "TOKEN_COMMENT";
	case TOKEN_ID: return "TOKEN_ID";
	case TOKEN_INT_NUMBER: return "TOKEN_INT_NUMBER";
	case TOKEN_REAL_NUMBER: return "TOKEN_REAL_NUMBER";
	case TOKEN_EOF: return "TOKEN_EOF";
	default:
		return "";	
	}
}

void print_parser_rule(char *rule) {
	fprintf(parser_report, "Rule(%s)\n", rule);
}
void print_parser_error(eTOKENS expected, Token *actual) {
	fprintf(parser_report, "Expected token of type %s at line: %d, Actual token of type %s, lexeme: %s.\n", getTokenName(expected), actual->lineNumber, getTokenName(actual->kind), actual->lexeme);
}

Token *error_recovery(eTOKENS expected, Token *cur_token) {
	print_parser_error(expected, cur_token);
	while (cur_token->kind /*not in follow(program)*/ && cur_token->kind != TOKEN_EOF)
	{
		cur_token = next_token();
	}
	return back_token();
}

void match(eTOKENS t) {
	Token *cur_token = next_token();
	if (cur_token->kind != t) {
		error_recovery(t, cur_token);
	}
}
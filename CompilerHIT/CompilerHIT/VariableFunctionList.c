#include "VariableFunctionList.h"

int follow[23][5] = {
	{ TOKEN_EOF, 30, 30, 30, 30 },
	{ TOKEN_CLOSE_CIRCULAR_PAR, TOKEN_SEMICOLON, 30 , 30 , 30 },
	{ TOKEN_CLOSE_CIRCULAR_PAR, TOKEN_SEMICOLON, 30 , 30 , 30 },
	{ TOKEN_CLOSE_CIRCULAR_PAR, TOKEN_SEMICOLON, 30 , 30 , 30 },
	{ TOKEN_ID, 30 , 30 , 30 , 30 },
	{ TOKEN_CLOSE_CIRCULAR_PAR, TOKEN_SEMICOLON, 30 , 30 , 30 },
	{ TOKEN_CLOSE_CIRCULAR_PAR, TOKEN_SEMICOLON, 30 , 30 , 30 },
	{ TOKEN_COMMA, TOKEN_SEMICOLON, TOKEN_CLOSE_CIRCULAR_PAR, 30 , 30 },
	{ TOKEN_COMMA, TOKEN_SEMICOLON, TOKEN_CLOSE_CIRCULAR_PAR, TOKEN_ASSIGNMENT, 30 },
	{ TOKEN_EOF, 30 , 30 , 30 , 30 },
	{ TOKEN_EOF, 30 , 30 , 30 , 30 },
	{ TOKEN_REAL_NUMBER, TOKEN_EOF, TOKEN_INT_NUMBER, TOKEN_VOID, 30 },
	{ TOKEN_ID, 30 , 30 , 30 , 30 },
	{ TOKEN_CLOSE_CIRCULAR_PAR, 30 , 30 , 30 , 30 },
	{ TOKEN_CLOSE_CURLY_PAR, TOKEN_END, 30 , 30 , 30 },
	{ TOKEN_CLOSE_CURLY_PAR, TOKEN_END, 30 , 30 , 30 },
	{ TOKEN_SEMICOLON, 30 , 30 , 30 , 30 },
	{ TOKEN_SEMICOLON, 30 , 30 , 30 , 30 },
	{ TOKEN_SEMICOLON, 30 , 30 , 30 , 30 },
	{ TOKEN_REAL_NUMBER, TOKEN_INT_NUMBER, TOKEN_SEMICOLON, TOKEN_EOF, TOKEN_VOID },
	{ TOKEN_CLOSE_CIRCULAR_PAR, 30 , 30 , 30 , 30 },
	{ TOKEN_SEMICOLON, 30 , 30 , 30 , 30 },
	{ TOKEN_SEMICOLON, 30 , 30 , 30 , 30 }
};

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
void print_parser_error(eTOKENS *expected, int size) {
	char *expected_str;
	int length = strlen(getTokenName(expected[0]));
	for (int i = 1;i < size;i++) {
		length += (strlen(getTokenName(expected[i])) + 4);
	}
	expected_str = (char*)calloc(sizeof(char), length + 1);
	strcat(expected_str, getTokenName(expected[0]));
	for (int i = 1;i < size;i++) {
		strcat(expected_str, " or ");
		strcat(expected_str, getTokenName(expected[i]));
	}
	if (cur_token->kind == TOKEN_EOF) {
		fprintf(parser_report, "Expected token of type %s at line: %d, Actual token of type %s\n", expected_str, cur_token->lineNumber, getTokenName(cur_token->kind));
	}
	else {
		fprintf(parser_report, "Expected token of type %s at line: %d, Actual token of type %s, lexeme: %s\n", expected_str, cur_token->lineNumber, getTokenName(cur_token->kind), cur_token->lexeme);
	}
}

void error_recovery(eVARIABLE var, eTOKENS *expected, int size) {
	print_parser_error(expected, size);
	int in_follow_flag = 1;
	while (in_follow_flag && cur_token->kind != TOKEN_EOF)
	{
		cur_token = next_token();
		for (int i = 0;i < 5;i++) {
			if (cur_token->kind == follow[var][i]) {
				in_follow_flag = 0;
			}
		}
	}
	cur_token = back_token();
}

void match(eTOKENS t) {
	cur_token = next_token();
	eTOKENS *expected = (eTOKENS*)malloc(sizeof(eTOKENS));
	*expected = t;
	if (cur_token->kind != t) {
		print_parser_error(expected, 1);
	}
}
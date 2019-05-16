#include "Parser.h"

int follow[23][5] = {  /*static table of follow(x) for each variable in grammar*/
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

const char* getTokenName(eTOKENS token) /*dictionary of eTOKEN to actual token "string"*/
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

void print_parser_rule(char *rule) { /*print variable rule in parser report file*/
	fprintf(parser_report, "Rule(%s)\n", rule);
}
void print_parser_error(eTOKENS *expected, int size) { /*print parser error in report file*/
	char *expected_str;
	int length = strlen(getTokenName(expected[0])); /*determine the size of string of all expected token names*/
	for (int i = 1;i < size;i++) {
		length += (strlen(getTokenName(expected[i])) + 4);
	}
	expected_str = (char*)calloc(sizeof(char), length + 1); /*allocate memory to string of expected token names*/
	strcat(expected_str, getTokenName(expected[0]));
	for (int i = 1;i < size;i++) { /*build a string of expected token names*/
		strcat(expected_str, " or ");
		strcat(expected_str, getTokenName(expected[i]));
	}
	if (cur_token->kind == TOKEN_EOF) { /*if current toke is EOF print the error*/
		fprintf(parser_report, "Expected token of type %s at line: %d, Actual token of type %s\n", expected_str, cur_token->lineNumber, getTokenName(cur_token->kind));
	}
	else { /*print parser error massege*/
		fprintf(parser_report, "Expected token of type %s at line: %d, Actual token of type %s, lexeme: %s\n", expected_str, cur_token->lineNumber, getTokenName(cur_token->kind), cur_token->lexeme);
	}
}

void error_recovery(eVARIABLE var, eTOKENS *expected, int size) { /*recover from parser error*/
	print_parser_error(expected, size); /*print massege in report file with expected tokens*/
	int in_follow_flag = 1; /*1 - current token not in follow(x)*/
	while (in_follow_flag && cur_token->kind != TOKEN_EOF) /*while current token no in follow(x) and its not EOF*/
	{
		cur_token = next_token(); /*get next token*/
		for (int i = 0;i < 5;i++) { /*check if token in follow(x)*/
			if (cur_token->kind == follow[var][i]) { /*if token in follow(x)*/
				in_follow_flag = 0; /*update flag*/
			}
		}
	}
	cur_token = back_token(); /*go one token back in purpose to resume parsing*/
}

void match(eTOKENS t) { /*check if current token is as expected*/
	cur_token = next_token(); /*get current token*/
	eTOKENS *expected = (eTOKENS*)malloc(sizeof(eTOKENS)); 
	*expected = t; /*save expected for printing purpose*/
	if (cur_token->kind != t) { /*if token is not as expected*/
		print_parser_error(expected, 1); /*print error in report file*/
	}
}
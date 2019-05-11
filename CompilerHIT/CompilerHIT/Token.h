#ifndef TOKEN_H
#define TOKEN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern FILE *yyin, *yyout;

typedef enum eTOKENS
{
	TOKEN_PROGRAM,
	TOKEN_END,
	TOKEN_REAL,
	TOKEN_INTEGER,
	TOKEN_VOID,
	TOKEN_RETURN,
	TOKEN_MUL,
	TOKEN_DIV,
	TOKEN_ASSIGNMENT,
	TOKEN_COMMA,
	TOKEN_SEMICOLON,
	TOKEN_OPEN_CIRCULAR_PAR,
	TOKEN_CLOSE_CIRCULAR_PAR,
	TOKEN_OPEN_SQUER_PAR,
	TOKEN_CLOSE_SQUER_PAR,
	TOKEN_OPEN_CURLY_PAR,
	TOKEN_CLOSE_CURLY_PAR,
	TOKEN_COMMENT,
	TOKEN_ID,
	TOKEN_INT_NUMBER,
	TOKEN_REAL_NUMBER,
	TOKEN_EOF
	/*
		Examples of tokens, add/change according to your needs.
		
		Alternative way to define tokens:
		#define TOKEN_INTEGER 1
		#define TOKEN_IF 2
		...........
	*/
}eTOKENS;

typedef struct Token
{
	eTOKENS kind;
	char *lexeme;
	int lineNumber;
}Token;

typedef struct Node
{
	Token *tokensArray;
	struct Node *prev;
	struct Node *next;
} Node;

void create_and_store_token(eTOKENS kind, char* lexeme, int numOfLine);
Token *next_token();
Token *back_token();
void match();

#endif
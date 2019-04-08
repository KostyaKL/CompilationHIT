%option noyywrap

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Token.h"

int lineNumber;

%}

DIGIT [0-9]
ID    [A-Za-z][A-Za-z_]*

%%
"program"	{create_and_store_token(TOKEN_PROGRAM, yytext, lineNumber);
		 fprintf(yyout, "Token of type %s was found in line %d. His lexema is %s\n",
		 getTokenKind(TOKEN_PROGRAM), lineNumber, yytext);}

"end"		{create_and_store_token(TOKEN_END, yytext, lineNumber);
		 fprintf(yyout, "Token of type %s was found in line %d. His lexema is %s\n",
		 getTokenKind(TOKEN_END), lineNumber, yytext);}

"real"		{create_and_store_token(TOKEN_REAL, yytext, lineNumber);
		 fprintf(yyout, "Token of type %s was found in line %d. His lexema is %s\n",
		 getTokenKind(TOKEN_REAL), lineNumber, yytext);}

"integer"	{create_and_store_token(TOKEN_INTEGER, yytext, lineNumber);
		 fprintf(yyout, "Token of type %s was found in line %d. His lexema is %s\n",
		 getTokenKind(TOKEN_INTEGER), lineNumber, yytext);}

"void"		{create_and_store_token(TOKEN_VOID, yytext, lineNumber);
		 fprintf(yyout, "Token of type %s was found in line %d. His lexema is %s\n",
		 getTokenKind(TOKEN_VOID), lineNumber, yytext);}

"return"	{create_and_store_token(TOKEN_RETURN, yytext, lineNumber);
		 fprintf(yyout, "Token of type %s was found in line %d. His lexema is %s\n",
		 getTokenKind(TOKEN_RETURN), lineNumber, yytext);}

"\n"		{lineNumber++;}

%%

void main()
{
	yyin = fopen("check.txt", "r");
	yyout = fopen("output.txt", "w");
	if (yyout)
		yylex();
	
	lineNumber = 1;
	
}
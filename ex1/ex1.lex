

%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Token.h"

int lineNumber = 1;

%}

DIGIT	        [0-9]
LETTER	        [a-zA-Z]
ID		        {LETTER}({LETTER}|{DIGIT})*("_"({LETTER}|{DIGIT})+)*
INT_NUMBER      0|[1-9]{DIGIT}*
REAL_NUMBER     0"."{DIGIT}*[1-9]|[1-9]{DIGIT}*"."{DIGIT}*[1-9]
EOF             <<EOF>>


%%

"program"		    {create_and_store_token(TOKEN_PROGRAM, yytext, lineNumber);
					fprintf(yyout, "Token of kind KEYWORD was found at line %d, lexeme: %s\n", lineNumber, yytext);}

"end"		        {create_and_store_token(TOKEN_END, yytext, lineNumber);
					fprintf(yyout, "Token of kind KEYWORD was found at line %d, lexeme: %s\n", lineNumber, yytext);}

"real"		        {create_and_store_token(TOKEN_REAL, yytext, lineNumber);
					fprintf(yyout, "Token of kind KEYWORD was found at line %d, lexeme: %s\n", lineNumber, yytext);}

"integer"		    {create_and_store_token(TOKEN_INTEGER, yytext, lineNumber);
					fprintf(yyout, "Token of kind KEYWORD was found at line %d, lexeme: %s\n", lineNumber, yytext);}

"void"		        {create_and_store_token(TOKEN_VOID, yytext, lineNumber);
					fprintf(yyout, "Token of kind KEYWORD was found at line %d, lexeme: %s\n", lineNumber, yytext);}

"return"		    {create_and_store_token(TOKEN_RETURN, yytext, lineNumber);
					fprintf(yyout, "Token of kind KEYWORD was found at line %d, lexeme: %s\n", lineNumber, yytext);}

"*"		        	{create_and_store_token(TOKEN_MUL, yytext, lineNumber);
		        	fprintf(yyout, "Token of kind AR OP was found at line %d, lexeme: %s\n", lineNumber, yytext);}

"/"		        	{create_and_store_token(TOKEN_DIV, yytext, lineNumber);
		        	fprintf(yyout, "Token of kind AR OP was found at line %d, lexeme: %s\n", lineNumber, yytext);}

"="		        	{create_and_store_token(TOKEN_ASSIGNMENT, yytext, lineNumber);
		        	fprintf(yyout, "Token of kind AR OP was found at line %d, lexeme: %s\n", lineNumber, yytext);}

","		        	{create_and_store_token(TOKEN_COMMA, yytext, lineNumber);
		        	fprintf(yyout, "Token of kind SEPARATION SIGN was found at line %d, lexeme: %s\n", lineNumber, yytext);}

";"		        	{create_and_store_token(TOKEN_SEMICOLON, yytext, lineNumber);
	        		fprintf(yyout, "Token of kind SEPARATION SIGN was found at line %d, lexeme: %s\n", lineNumber, yytext);}

"("	        		{create_and_store_token(TOKEN_OPEN_CIRCULAR_PAR, yytext, lineNumber);
	        		fprintf(yyout, "Token of kind SEPARATION SIGN was found at line %d, lexeme: %s\n", lineNumber, yytext);}

")"			        {create_and_store_token(TOKEN_CLOSE_CIRCULAR_PAR, yytext, lineNumber);
	        		fprintf(yyout, "Token of kind SEPARATION SIGN was found at line %d, lexeme: %s\n", lineNumber, yytext);}

"["		        	{create_and_store_token(TOKEN_OPEN_SQUER_PAR, yytext, lineNumber);
        			fprintf(yyout, "Token of kind SEPARATION SIGN was found at line %d, lexeme: %s\n", lineNumber, yytext);}

"]"		        	{create_and_store_token(TOKEN_CLOSE_SQUER_PAR, yytext, lineNumber);
        			fprintf(yyout, "Token of kind SEPARATION SIGN was found at line %d, lexeme: %s\n", lineNumber, yytext);}

"{"	        		{create_and_store_token(TOKEN_OPEN_CURLY_PAR, yytext, lineNumber);
			        fprintf(yyout, "Token of kind SEPARATION SIGN was found at line %d, lexeme: %s\n", lineNumber, yytext);}

"}"	        		{create_and_store_token(TOKEN_CLOSE_CURLY_PAR, yytext, lineNumber);
		        	fprintf(yyout, "Token of kind SEPARATION SIGN was found at line %d, lexeme: %s\n", lineNumber, yytext);}

"--".* 				{fprintf(yyout, "A COMMENT was found at line %d, lexeme: %s\n", lineNumber, yytext);}

"\n"				{lineNumber++;}

"\t"				{;}

" "					{;}

{ID}				{create_and_store_token(TOKEN_ID, yytext, lineNumber);
					fprintf(yyout, "Token of kind ID was found at line %d, lexeme: %s\n", lineNumber, yytext);}

{INT_NUMBER}		{create_and_store_token(TOKEN_INT_NUMBER, yytext, lineNumber);
		 			fprintf(yyout, "Token of kind NUMBER was found at line %d, lexeme: %s\n", lineNumber, yytext);}

{REAL_NUMBER}       {create_and_store_token(TOKEN_REAL_NUMBER, yytext, lineNumber);
		 			fprintf(yyout, "Token of kind REAL NUMBER was found at line %d, lexeme: %s\n", lineNumber, yytext);}

{EOF}				{create_and_store_token(TOKEN_EOF, yytext, lineNumber);
		 			fprintf(yyout, "Token of kind EOF was found at line %d", lineNumber);
					return;}

.					{fprintf(yyout, "The character %s at line %d does not begin any legal token in the language.\n", yytext, lineNumber);}
														

%%

int yywrap(void){return 1;}

void main(int argc, char* argv[])
{
	yyin = fopen("check.txt", "r");
	yyout = fopen("output.txt", "w");
	
	yylex();
	
}

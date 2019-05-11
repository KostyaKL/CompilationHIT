
%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Token.h"

int lineNumber = 1; /* line counter initialization */
void print2file(char*); /* declaration of method to print the token database to a text file */

%}

PROGRAM				"program"
END					"end"
REAL				"real"
INTEGER				"integer"
VOID				"void"
RETURN				"return"

MUL					"*"
DIV					"/"
ASSIGN				"="

COMMA				","
SEMICOLON			";"

OPEN_CIRCULAR_PAR	"("
CLOSE_CIRCULAR_PAR	")"
OPEN_SQUARE_PAR		"["
CLOSE_SQUARE_PAR	"]"
OPEN_CURLY_PAR		"{"
CLOSE_CURLY_PAR		"}"

COMMENT_SIGN		"--"
COMMENT				{COMMENT_SIGN}.*
NEW_LINE			"\n"
TAB					"\t"
SPACE				" "

DIGIT				[0-9]
NATURAL				[1-9]
LETTER				[a-zA-Z]
ID					{LETTER}({LETTER}|{DIGIT})*("_"({LETTER}|{DIGIT})+)*
INT_NUMBER			0|{NATURAL}{DIGIT}*
REAL_NUMBER			0"."{DIGIT}*{NATURAL}|{NATURAL}{DIGIT}*"."{DIGIT}*{NATURAL}

%%

{PROGRAM}				{create_and_store_token(TOKEN_PROGRAM, yytext, lineNumber);
						print2file("KEYWORD");}

{END}					{create_and_store_token(TOKEN_END, yytext, lineNumber);
						print2file("KEYWORD");}

{REAL}					{create_and_store_token(TOKEN_REAL, yytext, lineNumber);
						print2file("KEYWORD");}

{INTEGER}				{create_and_store_token(TOKEN_INTEGER, yytext, lineNumber);
						print2file("KEYWORD");}

{VOID}					{create_and_store_token(TOKEN_VOID, yytext, lineNumber);
						print2file("KEYWORD");}

{RETURN}				{create_and_store_token(TOKEN_RETURN, yytext, lineNumber);
						print2file("KEYWORD");}

{MUL}	        		{create_and_store_token(TOKEN_MUL, yytext, lineNumber);
		        		print2file("OPERATION");}

{DIV}		        	{create_and_store_token(TOKEN_DIV, yytext, lineNumber);
		        		print2file("OPERATION");}

{ASSIGN}		        {create_and_store_token(TOKEN_ASSIGNMENT, yytext, lineNumber);
						print2file("OPERATION");}

{COMMA}		        	{create_and_store_token(TOKEN_COMMA, yytext, lineNumber);
		        		print2file("SEPARATION SIGN");}

{SEMICOLON}		        {create_and_store_token(TOKEN_SEMICOLON, yytext, lineNumber);
	        			print2file("SEPARATION SIGN");}

{OPEN_CIRCULAR_PAR}	    {create_and_store_token(TOKEN_OPEN_CIRCULAR_PAR, yytext, lineNumber);
	        			print2file("SEPARATION SIGN");}

{CLOSE_CIRCULAR_PAR}	{create_and_store_token(TOKEN_CLOSE_CIRCULAR_PAR, yytext, lineNumber);
	        			print2file("SEPARATION SIGN");}

{OPEN_SQUARE_PAR}		{create_and_store_token(TOKEN_OPEN_SQUER_PAR, yytext, lineNumber);
        				print2file("SEPARATION SIGN");}

{CLOSE_SQUARE_PAR}		{create_and_store_token(TOKEN_CLOSE_SQUER_PAR, yytext, lineNumber);
        				print2file("SEPARATION SIGN");}

{OPEN_CURLY_PAR}	    {create_and_store_token(TOKEN_OPEN_CURLY_PAR, yytext, lineNumber);
						print2file("SEPARATION SIGN");}

{CLOSE_CURLY_PAR}	    {create_and_store_token(TOKEN_CLOSE_CURLY_PAR, yytext, lineNumber);
		        		print2file("SEPARATION SIGN");}

{COMMENT} 				{}

{NEW_LINE}				{lineNumber++;}

{TAB}					{}

{SPACE}					{}

{ID}					{create_and_store_token(TOKEN_ID, yytext, lineNumber);
						print2file("ID");}

{INT_NUMBER}			{create_and_store_token(TOKEN_INT_NUMBER, yytext, lineNumber);
		 				print2file("INT NUMBER");}

{REAL_NUMBER}			{create_and_store_token(TOKEN_REAL_NUMBER, yytext, lineNumber);
		 				print2file("REAL NUMBER");}

<<EOF>>					{create_and_store_token(TOKEN_EOF, yytext, lineNumber);
			 			print2file(1);
						return;}

.						{print2file(NULL);}
														

%%

int yywrap(void){return 1;}

void print2file(char *token_kind){ /* method to print the token database to a text file */
	if(token_kind == NULL){ /* if token not recognised print error */
		fprintf(yyout, "The character %s at line %d does not begin any legal token in the language.\n", yytext, lineNumber);
	}
	else if(token_kind == 1){ /* if end of file */
		fprintf(yyout, "Token of kind EOF was found at line %d", lineNumber);
	}
	else{ /* recognised tokens */
		fprintf(yyout, "Token of kind %s was found at line %d, lexeme: %s\n", token_kind, lineNumber, yytext);
	}
}

void main(int argc, char* argv[])
{
	yyin = fopen("C:\\temp\\test1.txt", "r");
	yyout = fopen("C:\\temp\\test1_311334544_310765821_lex.txt", "w");
	
	if(yyin){ /* if test is openned sucsessfully */
		yylex();

    	fclose(yyin);
    	fclose(yyout);
	}
	else{
		printf("no test1 file found\n");
	}

    yyin = fopen("C:\\temp\\test2.txt", "r");
	yyout = fopen("C:\\temp\\test2_311334544_310765821_lex.txt", "w");
	
	if(yyin){ /* if test is openned sucsessfully */
		lineNumber = 1; /* reset line counter */
		yylex();

    	fclose(yyin);
    	fclose(yyout);
	}
	else{
		printf("no test2 file found\n");
	}
	
}
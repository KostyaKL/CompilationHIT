
%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*#include "Token.h"  declare after yylex is declared */
#include "Token.h" /*moved from ex.lex declarations*/
#include "Parser.h"

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
REAL_NUMBER			0"."{DIGIT}+|{NATURAL}{DIGIT}*"."{DIGIT}+

%%

{PROGRAM}				{create_and_store_token(TOKEN_PROGRAM, yytext, lineNumber);
						print2file("TOKEN_PROGRAM");
						return TOKEN_PROGRAM;}

{END}					{create_and_store_token(TOKEN_END, yytext, lineNumber);
						print2file("TOKEN_END");
						return TOKEN_END;}

{REAL}					{create_and_store_token(TOKEN_REAL, yytext, lineNumber);
						print2file("TOKEN_REAL");
						return TOKEN_REAL;}

{INTEGER}				{create_and_store_token(TOKEN_INTEGER, yytext, lineNumber);
						print2file("TOKEN_INTEGER");
						return TOKEN_INTEGER;}

{VOID}					{create_and_store_token(TOKEN_VOID, yytext, lineNumber);
						print2file("TOKEN_VOID");
						return TOKEN_VOID;}

{RETURN}				{create_and_store_token(TOKEN_RETURN, yytext, lineNumber);
						print2file("TOKEN_RETURN");
						return TOKEN_RETURN;}

{MUL}	        		{create_and_store_token(TOKEN_MUL, yytext, lineNumber);
		        		print2file("TOKEN_MUL");
						return TOKEN_MUL;}

{DIV}		        	{create_and_store_token(TOKEN_DIV, yytext, lineNumber);
		        		print2file("TOKEN_DIV");
						return TOKEN_DIV;}

{ASSIGN}		        {create_and_store_token(TOKEN_ASSIGNMENT, yytext, lineNumber);
						print2file("TOKEN_ASSIGNMENT");
						return TOKEN_ASSIGNMENT;}

{COMMA}		        	{create_and_store_token(TOKEN_COMMA, yytext, lineNumber);
		        		print2file("TOKEN_COMMA");
						return TOKEN_COMMA;}

{SEMICOLON}		        {create_and_store_token(TOKEN_SEMICOLON, yytext, lineNumber);
	        			print2file("TOKEN_SEMICOLON");
						return TOKEN_SEMICOLON;}

{OPEN_CIRCULAR_PAR}	    {create_and_store_token(TOKEN_OPEN_CIRCULAR_PAR, yytext, lineNumber);
	        			print2file("TOKEN_OPEN_CIRCULAR_PAR");
						return TOKEN_OPEN_CIRCULAR_PAR;}

{CLOSE_CIRCULAR_PAR}	{create_and_store_token(TOKEN_CLOSE_CIRCULAR_PAR, yytext, lineNumber);
	        			print2file("TOKEN_CLOSE_CIRCULAR_PAR");
						return TOKEN_CLOSE_CIRCULAR_PAR;}

{OPEN_SQUARE_PAR}		{create_and_store_token(TOKEN_OPEN_SQUER_PAR, yytext, lineNumber);
        				print2file("TOKEN_OPEN_SQUER_PAR");
						return TOKEN_OPEN_SQUER_PAR;}

{CLOSE_SQUARE_PAR}		{create_and_store_token(TOKEN_CLOSE_SQUER_PAR, yytext, lineNumber);
        				print2file("TOKEN_CLOSE_SQUER_PAR");
						return TOKEN_CLOSE_SQUER_PAR;}

{OPEN_CURLY_PAR}	    {create_and_store_token(TOKEN_OPEN_CURLY_PAR, yytext, lineNumber);
						print2file("TOKEN_OPEN_CURLY_PAR");
						return TOKEN_OPEN_CURLY_PAR;}

{CLOSE_CURLY_PAR}	    {create_and_store_token(TOKEN_CLOSE_CURLY_PAR, yytext, lineNumber);
		        		print2file("TOKEN_CLOSE_CURLY_PAR");
						return TOKEN_CLOSE_CURLY_PAR;}

{COMMENT} 				{}

{NEW_LINE}				{lineNumber++;}

{TAB}					{}

{SPACE}					{}

{ID}					{create_and_store_token(TOKEN_ID, yytext, lineNumber);
						print2file("TOKEN_ID");
						return TOKEN_ID;}

{INT_NUMBER}			{create_and_store_token(TOKEN_INT_NUMBER, yytext, lineNumber);
		 				print2file("TOKEN_INT_NUMBER");
						return TOKEN_INT_NUMBER;}

{REAL_NUMBER}			{create_and_store_token(TOKEN_REAL_NUMBER, yytext, lineNumber);
		 				print2file("TOKEN_REAL_NUMBER");
						return TOKEN_REAL_NUMBER;}

<<EOF>>					{create_and_store_token(TOKEN_EOF, yytext, lineNumber);
			 			print2file("\v");
						return TOKEN_EOF;}

.						{print2file(NULL);}
														

%%

int yywrap(void){return 1;}

void print2file(char *token_kind){ /* method to print the token database to a text file */
	if(token_kind == NULL){ /* if token not recognised print error */
		fprintf(yyout, "The character %s at line %d does not begin any legal token in the language.\n", yytext, lineNumber);
	}
	else if(token_kind == "\v"){ /* if end of file */
		fprintf(yyout, "Token of kind TOKEN_EOF was found at line %d", lineNumber);
	}
	else{ /* recognised tokens */
		fprintf(yyout, "Token of kind %s was found at line %d, lexeme: %s\n", token_kind, lineNumber, yytext);
	}
}

void main(int argc, char* argv[])
{
	yyin = fopen("C:\\temp\\test1.txt", "r");
	yyout = fopen("C:\\temp\\test1_311334544_310765821_lex.txt", "w");
	parser_report = fopen("C:\\temp\\test1_311334544_310765821_syntactic.txt", "w");
	
	if(yyin){ /* if test is openned sucsessfully */
		parser(parser_report);

    	fclose(yyin);
    	fclose(yyout);
		fclose(parser_report);
	}
	else{
		printf("no test1 file found\n");
	}

	yyin = fopen("C:\\temp\\test2.txt", "r");
	yyout = fopen("C:\\temp\\test2_311334544_310765821_lex.txt", "w");
	parser_report = fopen("C:\\temp\\test2_311334544_310765821_syntactic.txt", "w");

	if (yyin) { /* if test is openned sucsessfully */
		lineNumber = 1; /*reset line counter*/
		reset_tokens();
		parser(parser_report);

		fclose(yyin);
		fclose(yyout);
		fclose(parser_report);
	}
	else {
		printf("no test2 file found\n");
	}
}
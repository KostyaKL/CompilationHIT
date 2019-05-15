#include "RecursiveDescentParser.h"

void parser() {
	/*for debuging*/
	/*Token *tmp;
	yylex();
	int flag = 1;
	while (flag)
	{
		tmp = next_token();
		if (tmp->kind == TOKEN_EOF) {
			fprintf(parser_report, "kind: %d, line: %d, lexeme: %s\n", tmp->kind, tmp->lineNumber, tmp->lexeme);
			flag = 0;
		}
		else {
			tmp = back_token();
			fprintf(parser_report, "%d) kind: %d, line: %d, lexeme: %s\n", flag++, tmp->kind, tmp->lineNumber, tmp->lexeme);
			next_token();
		}
	}*/
	/*for debuging*/
	parse_program();
	match(TOKEN_EOF);
}
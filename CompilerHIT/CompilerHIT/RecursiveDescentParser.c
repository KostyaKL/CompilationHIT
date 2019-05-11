#include "RecursiveDescentParser.h"
#include "Token.h"
#include "VariableFunctionList.h"

void parser(FILE *parser_report) {
	Token *tmp;
	yylex();
	int flag = 1;
	while (flag)
	{
		tmp = next_token();
		if (tmp->kind == TOKEN_EOF) {
			flag = 0;
		}
		else {
			fprintf(parser_report, "count: %d\n", flag++);
		}
	}
	//parse_program();
	match(TOKEN_EOF);
}
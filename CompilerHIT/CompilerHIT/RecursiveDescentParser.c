#include "RecursiveDescentParser.h"

void parser() {
	parse_program();
	match(TOKEN_EOF);
	fprintf(parser_report, "parser finished");
}
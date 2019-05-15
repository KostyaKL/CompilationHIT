#include "RecursiveDescentParser.h"

void parser() {
	parse_program();
	match(TOKEN_EOF);
}
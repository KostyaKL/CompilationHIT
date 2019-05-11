#include "RecursiveDescentParser.h"
#include "Token.h"
#include "VariableFunctionList.h"

void parser() {
	parse_program();
	match(TOKEN_EOF);
}
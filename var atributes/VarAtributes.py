rules = {"PROGRAM": "program VAR_DEFINITIONS; STATEMENTS end FUNC_DEFINITIONS",
         "VAR_DEFINITIONS": "VAR_DEFINITION VR_DFS'",
         "VR_DFS'": "epsilon | ; VAR_DEFINITIONS",
         "VAR_DEFINITION": "TYPE VARIABLES_LIST",
         "TYPE": "real | integer",
         "VARIABLES_LIST": "VARIABLE VRS_LST’",
         "VRS_LST’": "epsilon | ,VARIABLE VRS_LST’",
         "VARIABLE": "id VR'",
         "VR’": "epsilon | [int_number]",
         "FUNC_DEFINITIONS": "FUNC_DEFINITION FNC_DFS’",
         "FNC_DFS’": "epsilon | FUNC_DEFINITION FNC_DFS’",
         "FUNC_DEFINITION": "RETURNED_TYPE id (PARAM_DEFINITIONS) BLOCK",
         "RETURNED_TYPE": "void | TYPE",
         "PARAM_DEFINITIONS": "epsilon | VAR_DEFINITIONS",
         "STATEMENTS": "STATEMENT; STMS’",
         "STMS’": "epsilon | STATEMENTS",
         "STATEMENT": "BLOCK | return RTN_ST' | id ID_ST'",
         "RTN_ST'": "epsilon | EXPRESSION",
         "ID_ST'": "VR' = EXPRESSION | (PARAMETERS_LIST)",
         "BLOCK": "{ VAR_DEFINITIONS; STATEMENTS }",
         "FUNCTION_CALL": "id (PARAMETERS_LIST)",
         "PARAMETERS_LIST": "epsilon | VARIABLES_LIST",
         "EXPRESSION": "int_number | real_number | id EX'",
         "EX'": "VR' | ar_op EXPRESSION"
         }

result = {"nullable": {"PROGRAM": False,
                       "VAR_DEFINITIONS": False,
                       "VAR_DFS'": False,
                       "VAR_DEFINITION": False,
                       "TYPE": False,
                       "VARIABLES_LIST": False,
                       "VAR_LST'": False,
                       "VARIABLE": False,
                       "VR'": False,
                       "FUNC_DEFINITIONS": False,
                       "FUNC_DFS'": False,
                       "FUNC_DEFINITION": False,
                       "RETURNED_TYPE": False,
                       "PARAM_DEFINITIONS": False,
                       "STATEMENTS": False,
                       "STMS'": False,
                       "STATEMENT": False,
                       "RTN_ST'": False,
                       "ID_ST'": False,
                       "BLOCK": False,
                       "PARAMETERS_LIST": False,
                       "EXPRESSION": False,
                       "EX'": False}}

for x in rules:
    if rules[x].find("epsilon") >= 0:
        result["nullable"][x] = True

changed = True
while changed:
    changed = False
    for x in rules:
        for y in rules[x].split():
            if result["nullable"][y] not in rules or result["nullable"][y] is not True:
                nullable = False
                changed = False
                break
        if nullable:
            changed = True
            result["nullable"][x] = True

None
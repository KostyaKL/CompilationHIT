rules = {"PROGRAM": "program VAR_DEFINITIONS ; STATEMENTS end FUNC_DEFINITIONS",
         "VAR_DEFINITIONS": "VAR_DEFINITION VAR_DEFINITIONS#",
         "VAR_DEFINITIONS#": "epsilon | ; VAR_DEFINITIONS",
         "VAR_DEFINITION": "TYPE VARIABLES_LIST",
         "TYPE": "real | integer",
         "VARIABLES_LIST": "VARIABLE VARIABLES_LIST#",
         "VARIABLES_LIST#": "epsilon | , VARIABLE VARIABLES_LIST#",
         "VARIABLE": "id VARIABLE#",
         "VARIABLE#": "epsilon | [ int_number ]",
         "FUNC_DEFINITIONS": "FUNC_DEFINITION FUNC_DEFINITIONS#",
         "FUNC_DEFINITIONS#": "epsilon | FUNC_DEFINITION FUNC_DEFINITIONS#",
         "FUNC_DEFINITION": "RETURNED_TYPE id ( PARAM_DEFINITIONS ) BLOCK",
         "RETURNED_TYPE": "void | TYPE",
         "PARAM_DEFINITIONS": "epsilon | VAR_DEFINITIONS",
         "STATEMENTS": "STATEMENT ; STATEMENTS#",
         "STATEMENTS#": "epsilon | STATEMENTS",
         "STATEMENT": "BLOCK | return RETURN_STATEMENT# | id ID_STATEMENT#",
         "RETURN_STATEMENT#": "epsilon | EXPRESSION",
         "ID_STATEMENT#": "VARIABLE# = EXPRESSION | ( PARAMETERS_LIST )",
         "BLOCK": "{ VAR_DEFINITIONS ; STATEMENTS }",
         "PARAMETERS_LIST": "epsilon | VARIABLES_LIST",
         "EXPRESSION": "int_number | real_number | id EXPRESSION#",
         "EXPRESSION#": "VARIABLE# | ar_op EXPRESSION"
         }

result = {"nullable": {"PROGRAM": False,
                       "VAR_DEFINITIONS": False,
                       "VAR_DEFINITIONS#": False,
                       "VAR_DEFINITION": False,
                       "TYPE": False,
                       "VARIABLES_LIST": False,
                       "VARIABLES_LIST#": False,
                       "VARIABLE": False,
                       "VARIABLE#": False,
                       "FUNC_DEFINITIONS": False,
                       "FUNC_DEFINITIONS#": False,
                       "FUNC_DEFINITION": False,
                       "RETURNED_TYPE": False,
                       "PARAM_DEFINITIONS": False,
                       "STATEMENTS": False,
                       "STATEMENTS#": False,
                       "STATEMENT": False,
                       "RETURN_STATEMENT#": False,
                       "ID_STATEMENT#": False,
                       "BLOCK": False,
                       "PARAMETERS_LIST": False,
                       "EXPRESSION": False,
                       "EXPRESSION#": False},
          "first": {"PROGRAM": [],
                    "VAR_DEFINITIONS": [],
                    "VAR_DEFINITIONS#": [],
                    "VAR_DEFINITION": [],
                    "TYPE": [],
                    "VARIABLES_LIST": [],
                    "VARIABLES_LIST#": [],
                    "VARIABLE": [],
                    "VARIABLE#": [],
                    "FUNC_DEFINITIONS": [],
                    "FUNC_DEFINITIONS#": [],
                    "FUNC_DEFINITION": [],
                    "RETURNED_TYPE": [],
                    "PARAM_DEFINITIONS": [],
                    "STATEMENTS": [],
                    "STATEMENTS#": [],
                    "STATEMENT": [],
                    "RETURN_STATEMENT#": [],
                    "ID_STATEMENT#": [],
                    "BLOCK": [],
                    "PARAMETERS_LIST": [],
                    "EXPRESSION": [],
                    "EXPRESSION#": []},
          "follow": {"PROGRAM": ["EOF"],
                     "VAR_DEFINITIONS": [],
                     "VAR_DEFINITIONS#": [],
                     "VAR_DEFINITION": [],
                     "TYPE": [],
                     "VARIABLES_LIST": [],
                     "VARIABLES_LIST#": [],
                     "VARIABLE": [],
                     "VARIABLE#": [],
                     "FUNC_DEFINITIONS": [],
                     "FUNC_DEFINITIONS#": [],
                     "FUNC_DEFINITION": [],
                     "RETURNED_TYPE": [],
                     "PARAM_DEFINITIONS": [],
                     "STATEMENTS": [],
                     "STATEMENTS#": [],
                     "STATEMENT": [],
                     "RETURN_STATEMENT#": [],
                     "ID_STATEMENT#": [],
                     "BLOCK": [],
                     "PARAMETERS_LIST": [],
                     "EXPRESSION": [],
                     "EXPRESSION#": []}
          }

for x in rules:
    if rules[x].find("epsilon") >= 0:
        result["nullable"][x] = True

changed = True
while changed:
    changed = False
    for x in rules:
        nullable = True
        for y in rules[x].split():
            if y == "|" and nullable:
                break
            else:
                if y not in rules and y != "epsilon" and y != "|":
                    nullable = False
                    changed = False
                    break
                elif y in rules and result["nullable"][y] is not True:
                    nullable = False
                    changed = False
                    break
        if nullable and result["nullable"][x] is False:
            changed = True
            result["nullable"][x] = True


def first(x):
    ret = []
    tmp_rules = rules[x].split("|")
    for rule in tmp_rules:
        tmp_first = rule.split()[0]
        if tmp_first in rules:
            ret += first(tmp_first)
            ret = list(set(ret))
        else:
            if tmp_first != "epsilon" and tmp_first not in ret:
                ret.append(tmp_first)

        nullable_vars = []
        size = len(rule.split())
        for i in range(0, size):
            if rule.split()[i] in rules and i < size-1:
                if result["nullable"][rule.split()[i]] is False:
                    break
                else:
                    nullable_vars.append(rule.split()[i+1])
            else:
                break
        for null_var in nullable_vars:
            if null_var in rules:
                ret += first(null_var)
                ret = list(set(ret))
            else:
                if null_var != "epsilon" and null_var not in ret:
                    ret.append(null_var)
    return ret


for x in rules:
    result["first"][x] = first(x)


def follow_func(x):
    tmp_rules = rules[x].split("|")
    for rule in tmp_rules:
        size = len(rule.split())
        for i in range(0, size):
            if rule.split()[i] in rules and i < size - 1:
                if rule.split()[i+1] in rules:
                    result["follow"][rule.split()[i]] += result["first"][rule.split()[i+1]]
                    result["follow"][rule.split()[i]] = list(set(result["follow"][rule.split()[i]]))
                else:
                    if rule.split()[i+1] != "epsilon" and rule.split()[i+1] not in result["follow"][rule.split()[i]]:
                        result["follow"][rule.split()[i]].append(rule.split()[i+1])

                nullable_vars = []
                for j in range(i + 1, size):
                    if rule.split()[j] in rules and j < size - 1:
                        if result["nullable"][rule.split()[j]] is False:
                            break
                        else:
                            nullable_vars.append(rule.split()[j + 1])
                    else:
                        break

                for null_var in nullable_vars:
                    if null_var in rules:
                        result["follow"][rule.split()[i]] += result["first"][null_var]
                        result["follow"][rule.split()[i]] = list(set(result["follow"][rule.split()[i]]))
                    else:
                        if null_var != "epsilon" and null_var not in result["follow"][rule.split()[i]]:
                            result["follow"][rule.split()[i]].append(null_var)

                if j == size-1 and rule.split()[j] in rules and result["nullable"][rule.split()[j]] is True:
                    result["follow"][rule.split()[i]] += result["follow"][x]
                    result["follow"][rule.split()[i]] = list(set(result["follow"][rule.split()[i]]))
            if i == size - 1 and rule.split()[i] in rules:
                result["follow"][rule.split()[i]] += result["follow"][x]
                result["follow"][rule.split()[i]] = list(set(result["follow"][rule.split()[i]]))


for i in range(0, 23*23):
    for x in rules:
        follow_func(x)

with open('VarAtributes.csv', 'w') as f:
    printout = "Variables,Nullable,First,Follow"
    f.write(printout + "\n")
    for x in rules:
        printout = x + "," + str(result["nullable"][x]) + ",\"{" + str(result["first"][x])[1:-1] + "}\",\"{" + str(result["follow"][x])[1:-1] + "}\""
        f.write(printout + "\n")

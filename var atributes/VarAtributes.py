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
         "EXPRESSION#": "VARIABLE# | = EXPRESSION | * EXPRESSION | / EXPRESSION"
         }

var_atributes = {"nullable": {"PROGRAM": False,
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

predictive_table = {"PROGRAM":
                        {"program": [], "end": [], "real": [], "integer": [], "void": [],
                         "return": [], "=": [], "*": [], "/": [], ",": [], ";": [],
                         "(": [], ")": [], "[": [], "]": [], "{": [], "}": [],
                         "id": [], "int_number": [], "real_number": [], "EOF": []},
                    "VAR_DEFINITIONS":
                        {"program": [], "end": [], "real": [], "integer": [], "void": [],
                         "return": [], "=": [], "*": [], "/": [], ",": [], ";": [],
                         "(": [], ")": [], "[": [], "]": [], "{": [], "}": [],
                         "id": [], "int_number": [], "real_number": [], "EOF": []},
                    "VAR_DEFINITIONS#":
                        {"program": [], "end": [], "real": [], "integer": [], "void": [],
                         "return": [], "=": [], "*": [], "/": [], ",": [], ";": [],
                         "(": [], ")": [], "[": [], "]": [], "{": [], "}": [],
                         "id": [], "int_number": [], "real_number": [], "EOF": []},
                    "VAR_DEFINITION":
                        {"program": [], "end": [], "real": [], "integer": [], "void": [],
                         "return": [], "=": [], "*": [], "/": [], ",": [], ";": [],
                         "(": [], ")": [], "[": [], "]": [], "{": [], "}": [],
                         "id": [], "int_number": [], "real_number": [], "EOF": []},
                    "TYPE":
                        {"program": [], "end": [], "real": [], "integer": [], "void": [],
                         "return": [], "=": [], "*": [], "/": [], ",": [], ";": [],
                         "(": [], ")": [], "[": [], "]": [], "{": [], "}": [],
                         "id": [], "int_number": [], "real_number": [], "EOF": []},
                    "VARIABLES_LIST":
                        {"program": [], "end": [], "real": [], "integer": [], "void": [],
                         "return": [], "=": [], "*": [], "/": [], ",": [], ";": [],
                         "(": [], ")": [], "[": [], "]": [], "{": [], "}": [],
                         "id": [], "int_number": [], "real_number": [], "EOF": []},
                    "VARIABLES_LIST#":
                        {"program": [], "end": [], "real": [], "integer": [], "void": [],
                         "return": [], "=": [], "*": [], "/": [], ",": [], ";": [],
                         "(": [], ")": [], "[": [], "]": [], "{": [], "}": [],
                         "id": [], "int_number": [], "real_number": [], "EOF": []},
                    "VARIABLE":
                        {"program": [], "end": [], "real": [], "integer": [], "void": [],
                         "return": [], "=": [], "*": [], "/": [], ",": [], ";": [],
                         "(": [], ")": [], "[": [], "]": [], "{": [], "}": [],
                         "id": [], "int_number": [], "real_number": [], "EOF": []},
                    "VARIABLE#":
                        {"program": [], "end": [], "real": [], "integer": [], "void": [],
                         "return": [], "=": [], "*": [], "/": [], ",": [], ";": [],
                         "(": [], ")": [], "[": [], "]": [], "{": [], "}": [],
                         "id": [], "int_number": [], "real_number": [], "EOF": []},
                    "FUNC_DEFINITIONS":
                        {"program": [], "end": [], "real": [], "integer": [], "void": [],
                         "return": [], "=": [], "*": [], "/": [], ",": [], ";": [],
                         "(": [], ")": [], "[": [], "]": [], "{": [], "}": [],
                         "id": [], "int_number": [], "real_number": [], "EOF": []},
                    "FUNC_DEFINITIONS#":
                        {"program": [], "end": [], "real": [], "integer": [], "void": [],
                         "return": [], "=": [], "*": [], "/": [], ",": [], ";": [],
                         "(": [], ")": [], "[": [], "]": [], "{": [], "}": [],
                         "id": [], "int_number": [], "real_number": [], "EOF": []},
                    "FUNC_DEFINITION":
                        {"program": [], "end": [], "real": [], "integer": [], "void": [],
                         "return": [], "=": [], "*": [], "/": [], ",": [], ";": [],
                         "(": [], ")": [], "[": [], "]": [], "{": [], "}": [],
                         "id": [], "int_number": [], "real_number": [], "EOF": []},
                    "RETURNED_TYPE":
                        {"program": [], "end": [], "real": [], "integer": [], "void": [],
                         "return": [], "=": [], "*": [], "/": [], ",": [], ";": [],
                         "(": [], ")": [], "[": [], "]": [], "{": [], "}": [],
                         "id": [], "int_number": [], "real_number": [], "EOF": []},
                    "PARAM_DEFINITIONS":
                        {"program": [], "end": [], "real": [], "integer": [], "void": [],
                         "return": [], "=": [], "*": [], "/": [], ",": [], ";": [],
                         "(": [], ")": [], "[": [], "]": [], "{": [], "}": [],
                         "id": [], "int_number": [], "real_number": [], "EOF": []},
                    "STATEMENTS":
                        {"program": [], "end": [], "real": [], "integer": [], "void": [],
                         "return": [], "=": [], "*": [], "/": [], ",": [], ";": [],
                         "(": [], ")": [], "[": [], "]": [], "{": [], "}": [],
                         "id": [], "int_number": [], "real_number": [], "EOF": []},
                    "STATEMENTS#":
                        {"program": [], "end": [], "real": [], "integer": [], "void": [],
                         "return": [], "=": [], "*": [], "/": [], ",": [], ";": [],
                         "(": [], ")": [], "[": [], "]": [], "{": [], "}": [],
                         "id": [], "int_number": [], "real_number": [], "EOF": []},
                    "STATEMENT":
                        {"program": [], "end": [], "real": [], "integer": [], "void": [],
                         "return": [], "=": [], "*": [], "/": [], ",": [], ";": [],
                         "(": [], ")": [], "[": [], "]": [], "{": [], "}": [],
                         "id": [], "int_number": [], "real_number": [], "EOF": []},
                    "RETURN_STATEMENT#":
                        {"program": [], "end": [], "real": [], "integer": [], "void": [],
                         "return": [], "=": [], "*": [], "/": [], ",": [], ";": [],
                         "(": [], ")": [], "[": [], "]": [], "{": [], "}": [],
                         "id": [], "int_number": [], "real_number": [], "EOF": []},
                    "ID_STATEMENT#":
                        {"program": [], "end": [], "real": [], "integer": [], "void": [],
                         "return": [], "=": [], "*": [], "/": [], ",": [], ";": [],
                         "(": [], ")": [], "[": [], "]": [], "{": [], "}": [],
                         "id": [], "int_number": [], "real_number": [], "EOF": []},
                    "BLOCK":
                        {"program": [], "end": [], "real": [], "integer": [], "void": [],
                         "return": [], "=": [], "*": [], "/": [], ",": [], ";": [],
                         "(": [], ")": [], "[": [], "]": [], "{": [], "}": [],
                         "id": [], "int_number": [], "real_number": [], "EOF": []},
                    "PARAMETERS_LIST":
                        {"program": [], "end": [], "real": [], "integer": [], "void": [],
                         "return": [], "=": [], "*": [], "/": [], ",": [], ";": [],
                         "(": [], ")": [], "[": [], "]": [], "{": [], "}": [],
                         "id": [], "int_number": [], "real_number": [], "EOF": []},
                    "EXPRESSION":
                        {"program": [], "end": [], "real": [], "integer": [], "void": [],
                         "return": [], "=": [], "*": [], "/": [], ",": [], ";": [],
                         "(": [], ")": [], "[": [], "]": [], "{": [], "}": [],
                         "id": [], "int_number": [], "real_number": [], "EOF": []},
                    "EXPRESSION#":
                        {"program": [], "end": [], "real": [], "integer": [], "void": [],
                         "return": [], "=": [], "*": [], "/": [], ",": [], ";": [],
                         "(": [], ")": [], "[": [], "]": [], "{": [], "}": [],
                         "id": [], "int_number": [], "real_number": [], "EOF": []}
                    }

for x in rules:
    if rules[x].find("epsilon") >= 0:
        var_atributes["nullable"][x] = True

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
                elif y in rules and var_atributes["nullable"][y] is not True:
                    nullable = False
                    changed = False
                    break
        if nullable and var_atributes["nullable"][x] is False:
            changed = True
            var_atributes["nullable"][x] = True


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
            if rule.split()[i] in rules and i < size - 1:
                if var_atributes["nullable"][rule.split()[i]] is False:
                    break
                else:
                    nullable_vars.append(rule.split()[i + 1])
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
    var_atributes["first"][x] = first(x)


def follow_func(x):
    tmp_rules = rules[x].split("|")
    for rule in tmp_rules:
        size = len(rule.split())
        for i in range(0, size):
            if rule.split()[i] in rules and i < size - 1:
                if rule.split()[i + 1] in rules:
                    var_atributes["follow"][rule.split()[i]] += var_atributes["first"][rule.split()[i + 1]]
                    var_atributes["follow"][rule.split()[i]] = list(set(var_atributes["follow"][rule.split()[i]]))
                else:
                    if rule.split()[i + 1] != "epsilon" and rule.split()[i + 1] not in var_atributes["follow"][
                        rule.split()[i]]:
                        var_atributes["follow"][rule.split()[i]].append(rule.split()[i + 1])

                nullable_vars = []
                for j in range(i + 1, size):
                    if rule.split()[j] in rules and j < size - 1:
                        if var_atributes["nullable"][rule.split()[j]] is False:
                            break
                        else:
                            nullable_vars.append(rule.split()[j + 1])
                    else:
                        break

                for null_var in nullable_vars:
                    if null_var in rules:
                        var_atributes["follow"][rule.split()[i]] += var_atributes["first"][null_var]
                        var_atributes["follow"][rule.split()[i]] = list(set(var_atributes["follow"][rule.split()[i]]))
                    else:
                        if null_var != "epsilon" and null_var not in var_atributes["follow"][rule.split()[i]]:
                            var_atributes["follow"][rule.split()[i]].append(null_var)

                if j == size - 1 and rule.split()[j] in rules and var_atributes["nullable"][rule.split()[j]] is True:
                    var_atributes["follow"][rule.split()[i]] += var_atributes["follow"][x]
                    var_atributes["follow"][rule.split()[i]] = list(set(var_atributes["follow"][rule.split()[i]]))
            if i == size - 1 and rule.split()[i] in rules:
                var_atributes["follow"][rule.split()[i]] += var_atributes["follow"][x]
                var_atributes["follow"][rule.split()[i]] = list(set(var_atributes["follow"][rule.split()[i]]))


for i in range(0, 23 * 23):
    for x in rules:
        follow_func(x)

for rule in rules:
    current_rules = rules[rule].split("|")
    for current_rule in current_rules:
        alfa = current_rule.split()[0]
        if alfa in rules:
            for token in var_atributes["first"][alfa]:
                predictive_table[rule][token].append(current_rule)
                predictive_table[rule][token] = list(set(predictive_table[rule][token]))
        elif alfa != "epsilon":
            predictive_table[rule][alfa].append(current_rule)
            predictive_table[rule][alfa] = list(set(predictive_table[rule][alfa]))

        alfa_null = True
        for var in current_rule.split():
            if var in rules and var_atributes["nullable"][var] is False:
                alfa_null = False
                break
            elif var not in rules:
                alfa_null = False
                break
        if alfa_null:
            for token in var_atributes["follow"][rule]:
                predictive_table[rule][token].append(current_rule)
                predictive_table[rule][token] = list(set(predictive_table[rule][token]))

with open('VarAtributes.csv', 'w') as f:
    printout = "Variables,Nullable,First,Follow"
    f.write(printout + "\n")
    for x in rules:
        printout = x + "," + str(var_atributes["nullable"][x]) + ",\"{" + str(var_atributes["first"][x])[1:-1] + "}\",\"{" + str(var_atributes["follow"][x])[1:-1] + "}\""
        f.write(printout + "\n")

with open('PredictiveTable.csv', 'w') as f:
    printout = "TOKEN"
    for rule in rules:
        printout += ",\"" + rule + "\""
    f.write(printout + "\n")
    for token in predictive_table["PROGRAM"]:
        printout = "\"" + token + "\""
        for rule in predictive_table:
            printout += ",\"" + str(predictive_table[rule][token])[2:-2] + "\""
        f.write(printout + "\n")


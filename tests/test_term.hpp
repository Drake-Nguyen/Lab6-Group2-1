#include "../lexer.hpp"
#include "../procedure_functions.h"

#include "./utils.hpp"
#define macro TEST_NO_MAIN

#include <map>
#include <sstream>

static void test_term(void)
{

    // test (procedure_Primary, "",{}, CURRENT_LOCATION);
    test(procedure_Term, "x", {{"Identifier", "x"}}, CURRENT_LOCATION);
    test(procedure_Term, "2*y", {{"Integer", "2"}, {"Operator", "*"}, {"Identifier", "y"}}, CURRENT_LOCATION);
    test(procedure_Term, "3*z/4", {{"Integer", "3"}, {"Operator", "*"}, {"Identifier", "z"}, {"Operator", "/"}, {"Integer", "4"}}, CURRENT_LOCATION);
    test(procedure_Term, "3z/4", {{"Integer", "3"}, {"Identifier", "z"}, {"Operator", "/"}, {"Integer", "4"}}, CURRENT_LOCATION);
    test(procedure_Term, "2.5*x", {{"Real", "2.5"}, {"Operator", "*"}, {"Identifier", "x"}}, CURRENT_LOCATION);
    test(procedure_Term, "1.23*(y+z)", {{"Real", "1.23"}, {"Operator", "*"}, {"Separator", "("}, {"Identifier", "y"}, {"Operator", "+"}, {"Identifier", "z"}, {"Separator", ")"}}, CURRENT_LOCATION);
}
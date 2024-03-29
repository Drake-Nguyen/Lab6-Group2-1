#include "../lexer.hpp"
#include "../procedure_functions.h"

#include "./utils.hpp"
#define macro TEST_NO_MAIN

#include <map>
#include <sstream>

static void test_expression(void) {
  test(procedureExpression, "", {}, CURRENT_LOCATION);
  test(procedureExpression, "a = 10;",
       {{"Identifier", "a"},
        {"Other Separators", " "},
        {"Operator", "="},
        {"Other Separators", " "},
        {"Integer", "10"},
        {"Separator", ";"}},
       CURRENT_LOCATION);
  test(procedureExpression, "int a = b;",
       {{"Keyword", "int"},
        {"Other Separators", " "},
        {"Identifier", "a"},
        {"Other Separators", " "},
        {"Operator", "="},
        {"Other Separators", " "},
        {"Identifier", "b"},
        {"Separator", ";"}},
       CURRENT_LOCATION);
  test(procedureExpression, "int a;",
       {{"Keyword", "int"},
        {"Other Separators", " "},
        {"Identifier", "a"},
        {"Separator", ";"}},
       CURRENT_LOCATION);
  test(procedureExpression, "a+=10",
       {{"Identifier", "a"},
        {"Operator", "+"},
        {"Operator", "="},
        {"Integer", "10"}},
       CURRENT_LOCATION);
}
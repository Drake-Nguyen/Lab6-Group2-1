#include "../lexer.hpp"
#include "../procedure_functions.h"

#include "./utils.hpp"
#define macro TEST_NO_MAIN

#include <map>
#include <sstream>

static void test_term(void) {

  // test (procedurePrimary, "",{}, CURRENT_LOCATION);
  test(procedureTerm, "x", {{"Identifier", "x"}}, CURRENT_LOCATION);
  test(procedureTerm, "2*y",
       {{"Integer", "2"}, {"Operator", "*"}, {"Identifier", "y"}},
       CURRENT_LOCATION);
  test(procedureTerm, "3*z/4",
       {{"Integer", "3"},
        {"Operator", "*"},
        {"Identifier", "z"},
        {"Operator", "/"},
        {"Integer", "4"}},
       CURRENT_LOCATION);
  test(procedureTerm, "3z/4",
       {{"Invalid Token", "3z"}, {"Operator", "/"}, {"Integer", "4"}},
       CURRENT_LOCATION);
  test(procedureTerm, "3 z / 4",
       {{"Integer", "3"},
        {"Other Separators", " "},
        {"Identifier", "z"},
        {"Other Separators", " "},
        {"Operator", "/"},
        {"Other Separators", " "},
        {"Integer", "4"}},
       CURRENT_LOCATION);
  test(procedureTerm, "3zz z / 4",
       {{"Invalid Token", "3zz"},
        {"Other Separators", " "},
        {"Identifier", "z"},
        {"Other Separators", " "},
        {"Operator", "/"},
        {"Other Separators", " "},
        {"Integer", "4"}},
       CURRENT_LOCATION);
  test(procedureTerm, "2.5*x",
       {{"Real", "2.5"}, {"Operator", "*"}, {"Identifier", "x"}},
       CURRENT_LOCATION);
  test(procedureTerm, "1.23*(y+z)",
       {{"Real", "1.23"},
        {"Operator", "*"},
        {"Separator", "("},
        {"Identifier", "y"},
        {"Operator", "+"},
        {"Identifier", "z"},
        {"Separator", ")"}},
       CURRENT_LOCATION);
}
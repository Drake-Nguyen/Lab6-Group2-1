#include "../lexer.hpp"
#include "../procedure_functions.h"

#include "./utils.hpp"
#define macro TEST_NO_MAIN

#include <map>
#include <sstream>

static void test_return(void) {
  // Test empty return statement
  test(procedure_Return, "return;", {{"Keyword", "return"}, {"Separator", ";"}},
       CURRENT_LOCATION);
  test(procedure_Return, "return ;",
       {{"Keyword", "return"}, {"Other Separators", " "}, {"Separator", ";"}},
       CURRENT_LOCATION);
  test(procedure_Return, "return", {{"Keyword", "return"}}, CURRENT_LOCATION);

  test(procedure_Return, "return 2*x+3;",
       {{"Keyword", "return"},
        {"Other Separators", " "},
        {"Integer", "2"},
        {"Operator", "*"},
        {"Identifier", "x"},
        {"Operator", "+"},
        {"Integer", "3"},
        {"Separator", ";"}},
       CURRENT_LOCATION);

  test(procedure_Return, "return true;",
       {{"Keyword", "return"},
        {"Other Separators", " "},
        {"Keyword", "true"},
        {"Separator", ";"}},
       CURRENT_LOCATION);

  test(procedure_Return, "return x > 0;",
       {{"Keyword", "return"},
        {"Other Separators", " "},
        {"Identifier", "x"},
        {"Other Separators", " "},
        {"Operator", ">"},
        {"Other Separators", " "},
        {"Integer", "0"},
        {"Separator", ";"}},
       CURRENT_LOCATION);

  test(procedure_Return, "return x+1, y*2, z;",
       {{"Keyword", "return"},
        {"Other Separators", " "},
        {"Identifier", "x"},
        {"Operator", "+"},
        {"Integer", "1"},
        {"Separator", ","},
        {"Other Separators", " "},
        {"Identifier", "y"},
        {"Operator", "*"},
        {"Integer", "2"},
        {"Separator", ","},
        {"Other Separators", " "},
        {"Identifier", "z"},
        {"Separator", ";"}},
       CURRENT_LOCATION);
}

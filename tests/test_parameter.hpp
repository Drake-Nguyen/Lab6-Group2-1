#include "../lexer.hpp"
#include "../procedure_functions.h"

#include "./utils.hpp"
#define macro TEST_NO_MAIN

#include <map>
#include <sstream>

static void test_parameter(void) {
  test(procedure_Parameter, "a()",
       {{"Identifier", "a"}, {"Separator", "("}, {"Separator", ")"}},
       CURRENT_LOCATION);
  test(procedure_Parameter, "a(int x, int y)",
       {{"Identifier", "a"},
        {"Separator", "("},
        {"Keyword", "int"},
        {"Other Separators", " "},
        {"Identifier", "x"},
        {"Separator", ","},
        {"Other Separators", " "},
        {"Keyword", "int"},
        {"Other Separators", " "},
        {"Identifier", "y"},
        {"Separator", ")"}},
       CURRENT_LOCATION);
  test(procedure_Parameter, "a(10)",
       {{"Identifier", "a"},
        {"Separator", "("},
        {"Integer", "10"},
        {"Separator", ")"}},
       CURRENT_LOCATION);
}
#include "../lexer.hpp"
#include "../procedure_functions.h"

#include "./utils.hpp"
#define macro TEST_NO_MAIN

#include <map>
#include <sstream>

static void test_qualifier (void) {

  test (procedure_Qualifier, "static", {{"Keyword", "static"}}, CURRENT_LOCATION);
  test (procedure_Qualifier, "*", {{"Operator", "*"}}, CURRENT_LOCATION);
  test (procedure_Qualifier, "&", {{"Other Separators", "&"}}, CURRENT_LOCATION);
  test (procedure_Qualifier, "unsigned", {{"Keyword", "unsigned"}}, CURRENT_LOCATION);
  test (procedure_Qualifier, "int", {{"Keyword", "int"}}, CURRENT_LOCATION);
  test (procedure_Qualifier, "char", {{"Keyword", "char"}}, CURRENT_LOCATION);

  // Thanks to Diamond Dinh for these test cases
  test (procedure_Qualifier, "5", {{"Integer", "5"}}, CURRENT_LOCATION);
  test (procedure_Qualifier, "true", {{"Keyword", "true"}}, CURRENT_LOCATION);


}

#include "../lexer.hpp"
#include "../procedure_functions.h"

#include "./utils.hpp"
#define macro TEST_NO_MAIN

#include <map>
#include <sstream>

static void test_assign(void) {
  // valid assignment
  test(procedure_Assign, "a = 123;", {}, CURRENT_LOCATION);

  // invalid assignments
  test(procedure_Assign, "", {}, CURRENT_LOCATION);  // empty input
  test(procedure_Assign, "a = ;", {}, CURRENT_LOCATION);  // missing expression
  test(procedure_Assign, "a = 123", {}, CURRENT_LOCATION);  // missing semicolon
  test(procedure_Assign, "a 123;", {}, CURRENT_LOCATION);  // missing assignment operator
  test(procedure_Assign, "123 = a;", {}, CURRENT_LOCATION);  // invalid left-hand side
}


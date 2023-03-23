#include "../lexer.hpp"
#include "../procedure_functions.h"

#include "./utils.hpp"
#define macro TEST_NO_MAIN

#include <map>
#include <sstream>

static void test_assign(void) {
  // valid assignment
  test(procedureAssign, "a = 123;", {}, CURRENT_LOCATION);

  // invalid assignments

  test(procedureAssign, "", {}, CURRENT_LOCATION);        // empty input
  test(procedureAssign, "a = ;", {}, CURRENT_LOCATION);   // missing expression
  test(procedureAssign, "a = 123", {}, CURRENT_LOCATION); // missing semicolon
  test(procedureAssign, "a 123;", {},
       CURRENT_LOCATION); // missing assignment operator
  test(procedureAssign, "123 = a;", {},
       CURRENT_LOCATION); // invalid left-hand side
}

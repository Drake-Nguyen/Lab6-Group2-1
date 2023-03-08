#include "../lexer.hpp"
#include "../procedure_functions.h"

#include "./utils.hpp"
#define macro TEST_NO_MAIN

#include <map>
#include <sstream>

static void test_declaration(void) {
  // valid declarations
  test(procedure_Declaration, "int x;", {}, CURRENT_LOCATION);
  test(procedure_Declaration, "float x, y, z;", {}, CURRENT_LOCATION);
  test(procedure_Declaration, "char c, d;", {}, CURRENT_LOCATION);

  // invalid declarations
  test_fail(procedure_Declaration, "int 123;", {}, CURRENT_LOCATION);
  test_fail(procedure_Declaration, "bool x;", {}, CURRENT_LOCATION);
  test_fail(procedure_Declaration, "int x,;", {}, CURRENT_LOCATION);
  test_fail(procedure_Declaration, "float x y z;", {}, CURRENT_LOCATION);
  test_fail(procedure_Declaration, "char ,d;", {}, CURRENT_LOCATION);
}

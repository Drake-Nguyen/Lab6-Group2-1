#include "../lexer.hpp"
#include "../procedure_functions.h"

#include "./utils.hpp"
#define macro TEST_NO_MAIN

#include <map>
#include <sstream>

static void test_declaration(void) {
  // valid declarations
  test(procedureDeclaration, "int x;", {}, CURRENT_LOCATION);
  test(procedureDeclaration, "float x, y, z;", {}, CURRENT_LOCATION);
  test(procedureDeclaration, "char c, d;", {}, CURRENT_LOCATION);

  // invalid declarations
  test_fail(procedureDeclaration, "int 123;", {}, CURRENT_LOCATION);
  test_fail(procedureDeclaration, "bool x;", {}, CURRENT_LOCATION);
  test_fail(procedureDeclaration, "int x,;", {}, CURRENT_LOCATION);
  test_fail(procedureDeclaration, "float x y z;", {}, CURRENT_LOCATION);
  test_fail(procedureDeclaration, "char ,d;", {}, CURRENT_LOCATION);
}

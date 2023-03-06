#include "../lexer.hpp"
#include "../procedure_functions.h"

#include "./utils.hpp"
#define macro TEST_NO_MAIN

#include <map>
#include <sstream>

static void test_term(void) {
  test(procedure_term, "3y", {{"Operator", "3y"}}, CURRENT_LOCATION);
  test(procedure_term, "10", {{"Operator", "10"}}, CURRENT_LOCATION);
  test(procedure_term, "<", {{"Operator", "<"}}, CURRENT_LOCATION);
  test(procedure_term, "<=", {{"Operator", "<="}}, CURRENT_LOCATION);
  test(procedure_term, ">", {{"Operator", ">"}}, CURRENT_LOCATION);
  test(procedure_term, ">=", {{"Operator", ">="}}, CURRENT_LOCATION);
}

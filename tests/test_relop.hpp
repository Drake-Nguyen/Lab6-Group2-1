#include "../lexer.hpp"
#include "../procedure_functions.h"

#include "./utils.hpp"
#define macro TEST_NO_MAIN

#include <map>
#include <sstream>

static void test_relop(void) {
  test(procedure_Relop, "==", {{"Operator", "=="}}, CURRENT_LOCATION);
  test(procedure_Relop, "!=", {{"Operator", "!="}}, CURRENT_LOCATION);
  test(procedure_Relop, "<", {{"Operator", "<"}}, CURRENT_LOCATION);
  test(procedure_Relop, "<=", {{"Operator", "<="}}, CURRENT_LOCATION);
  test(procedure_Relop, ">", {{"Operator", ">"}}, CURRENT_LOCATION);
  test(procedure_Relop, ">=", {{"Operator", ">="}}, CURRENT_LOCATION);
}

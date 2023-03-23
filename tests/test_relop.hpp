#include "../lexer.hpp"
#include "../procedure_functions.h"

#include "./utils.hpp"
#define macro TEST_NO_MAIN

#include <map>
#include <sstream>

static void test_relop(void) {
test(procedureRelop, "==", {{"Operator", "=="}}, CURRENT_LOCATION);
test(procedureRelop, "!=", {{"Operator", "!="}}, CURRENT_LOCATION);
test(procedureRelop, "<", {{"Operator", "<"}}, CURRENT_LOCATION);
test(procedureRelop, "<=", {{"Operator", "<="}}, CURRENT_LOCATION);
test(procedureRelop, ">", {{"Operator", ">"}}, CURRENT_LOCATION);
test(procedureRelop, ">=", {{"Operator", ">="}}, CURRENT_LOCATION);

test_fail(procedureRelop, "=!", {}, CURRENT_LOCATION);
test_fail(procedureRelop, "!", {}, CURRENT_LOCATION);
test_fail(procedureRelop, "=", {}, CURRENT_LOCATION);
}

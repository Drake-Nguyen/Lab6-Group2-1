#include "../lexer.hpp"
#include "../procedure_functions.h"

#include "./utils.hpp"
#define macro TEST_NO_MAIN

#include <map>
#include <sstream>

static void test_condition(void) {
const auto t = [](std::string lhs, std::string op, std::string rhs,
const char *file, int line) {
test(procedureCondition, lhs + " " + op + " " + rhs,
{{"Keyword", lhs},{"Other Separators", " "},{"Operator", op},
{"Other Separators", " "},{"Keyword", rhs},},file, line);};

t("true", "==", "true", CURRENT_LOCATION);
t("true", "!=", "false", CURRENT_LOCATION);
t("123", "<", "345", CURRENT_LOCATION);
t("456", ">", "123", CURRENT_LOCATION);
}

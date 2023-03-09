#include "../lexer.hpp"
#include "../procedure_functions.h"

#include "./utils.hpp"
#define macro TEST_NO_MAIN

#include <map>
#include <sstream>

static void test_qualifier (void) {

test (procedure_Qualifier, "int", {{"Keyword", "int"}}, CURRENT_LOCATION);
test (procedure_Qualifier, "boolean", {{"Keyword", "boolean"}}, CURRENT_LOCATION);
test (procedure_Qualifier, "real", {{"Keyword", "real"}}, CURRENT_LOCATION);

test_fail (procedure_Qualifier, "static", {{"Keyword", "static"}}, CURRENT_LOCATION);
test_fail (procedure_Qualifier, "char", {{"Keyword", "char"}}, CURRENT_LOCATION);

}

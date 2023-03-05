#include "../lexer.hpp"
#include "../procedure_functions.h"

#include "./utils.hpp"
#define macro TEST_NO_MAIN

#include <map>
#include <sstream>

static void test_qualifier_boolean(void) {
  test(procedure_Qualifier, "true", {{"Keyword", "true"}}, CURRENT_LOCATION);
}

static void test_qualifier_int(void) {
  test(procedure_Qualifier, "123", {{"Integer", "123"}}, CURRENT_LOCATION);
}

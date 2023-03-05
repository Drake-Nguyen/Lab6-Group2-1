#include "../lexer.hpp"
#include "../procedure_functions.h"

#include "../include/acutest.h"
#include "./utils.hpp"

#include <map>
#include <sstream>

#define macro TEST_NO_MAIN

static void test_qualifier_boolean(void) {
  test(procedure_Qualifier, "true", {{"Keyword", "true"}}, CURRENT_LOCATION);
}

static void test_qualifier_int(void) {
  test(procedure_Qualifier, "123", {{"Integer", "123"}}, CURRENT_LOCATION);
}

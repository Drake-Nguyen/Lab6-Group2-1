#include "../lexer.hpp"
#include "../procedure_functions.h"

#include "../include/acutest.h"
#include "./utils.hpp"

#include <sstream>

#define macro TEST_NO_MAIN

void test_qualifier(void) {
  auto tokens = parse_tokens("123");
  TEST_EQUAL(tokens.size(), (size_t)1);
  TEST_EQUAL(tokens[0].token(), "Keyword");
  TEST_EQUAL(tokens[0].lexeme(), "123");
}

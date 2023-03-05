#pragma once

#include <iomanip>
#include <type_traits>

#include "../lexer.hpp"

#include "../include/acutest.h"
#define macro TEST_NO_MAIN

vector<token_323> parse_tokens(std::string input) {
  std::stringstream ss(input);
  std::vector<token_323> tokens;
  while (true) {
    auto token = lexer_323(ss);
    if (token.token() == "none") {
      break;
    }
    tokens.push_back(token);
  }
  return tokens;
}

void test_equal_(std::string a, std::string b, const char *file, int line) {
  if (a != b) {
    std::stringstream ss;
    ss << std::quoted(a) << " != " << std::quoted(b);
    acutest_check_(false, file, line, "%s", ss.str().c_str());
  }
}

template <typename T, class = typename std::enable_if_t<std::is_integral_v<T>>>
void test_equal_(T a, T b, const char *file, int line) {
  if (a != b) {
    auto err = std::to_string(a) + " != " + std::to_string(b);
    acutest_check_(false, file, line, "%s", err.c_str());
  }
}

#define TEST_EQUAL(a, b) test_equal_(a, b, __FILE__, __LINE__)

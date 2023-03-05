#pragma once

#include <algorithm>
#include <cassert>
#include <initializer_list>
#include <iomanip>
#include <map>
#include <source_location>
#include <type_traits>
#include <vector>

#include "../lexer.hpp"

#include "../include/acutest.h"
#define macro TEST_NO_MAIN

#define TEST_EQUAL(a, b) test_equal_(a, b, __FILE__, __LINE__)

#define CURRENT_LOCATION __FILE__, __LINE__

static vector<token_323> parseTokens(std::string input) {
  // lexer_323 is hopelessly broken and does not treat EOF right. We can add a
  // whitespace to prevent EOF from being treated as an error.
  std::stringstream ss(input + " ");

  std::vector<token_323> tokens;
  while (true) {
    auto token = lexer_323(ss);
    if (token.token() == "none") {
      break;
    }
    tokens.push_back(token);
  }

  // Ignore the last token, which is a whitespace.
  assert(tokens.back().token() == "Other Separators");
  tokens.pop_back();

  return tokens;
}

static void test_equal_(std::string a, std::string b, const char *file,
                        int line, const std::string what = "") {
  if (a != b) {
    std::stringstream ss;
    if (what != "") {
      ss << what << ": ";
    }
    ss << std::quoted(a) << " != " << std::quoted(b);
    acutest_check_(false, file, line, "%s", ss.str().c_str());
  }
}

template <
    typename T1, class = typename std::enable_if_t<std::is_integral_v<T1>>,
    typename T2, class = typename std::enable_if_t<std::is_integral_v<T2>>>
void test_equal_(T1 a, T2 b, const char *file, int line,
                 const std::string what = "") {
  if (a != b) {
    std::string err;
    if (what != "") {
      err = what + ": ";
    }
    err += std::to_string(a) + " != " + std::to_string(b);
    acutest_check_(false, file, line, "%s", err.c_str());
  }
}

struct ExpectToken {
  std::string token;
  std::string lexeme;
};

static void test(std::function<bool(std::vector<token_323> &, int &)> procedure,
                 std::string input, std::initializer_list<ExpectToken> expects,
                 const char *file, int line) {

  auto tokens = parseTokens(input);

  if (tokens.size() != expects.size()) {
    test_equal_(tokens.size(), expects.size(), file, line);
    return;
  }

  auto it = expects.begin();
  for (size_t i = 0; i < tokens.size(); i++) {
    test_equal_(tokens[i].token(), it->token, file, line,
                "token " + to_string(i) + " token");
    test_equal_(tokens[i].lexeme(), it->lexeme, file, line,
                "token " + to_string(i) + " lexeme");
    it++;
  }

  int loc = 0;
  auto res = procedure(tokens, loc);
  acutest_check_(res, file, line, "%s", "procedure");
}
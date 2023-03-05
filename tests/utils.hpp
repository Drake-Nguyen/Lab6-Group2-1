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

  // Ignore the last few tokens, which are whitespaces.
  while (tokens.back().token() == "Other Separators" &&
         tokens.back().lexeme() == " ") {
    tokens.pop_back();
  }

  return tokens;
}

static std::string quote(std::string s) {
  std::stringstream ss;
  ss << std::quoted(s);
  return ss.str();
}

static void test_equal_(std::string a, std::string b, const char *file,
                        int line, const std::string what = "") {
  if (a != b) {
    std::string err;
    if (what != "") {
      err = what + ": ";
    }
    err += quote(a) + " != " + quote(b);
    acutest_check_(false, file, line, "%s", err.c_str());
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

  TEST_CASE(quote(input).c_str());

  auto tokens = parseTokens(input);

  if (expects.size() != 0) {
    test_equal_(tokens.size(), expects.size(), file, line,
                "tokens.size mismatch");

    auto it = expects.begin();
    for (size_t i = 0; i < min(tokens.size(), expects.size()); i++) {
      test_equal_(tokens[i].token(), it->token, file, line,
                  "token [" + to_string(i) + "]: token mismatch");
      test_equal_(tokens[i].lexeme(), it->lexeme, file, line,
                  "token [" + to_string(i) + "]: lexeme mismatch");
      it++;
    }

    for (size_t i = expects.size(); i < tokens.size(); i++) {
      auto v = tokens[i];
      acutest_check_(false, file, line,
                     "erroneous extra token [%ld]: { token: %s, lexeme: %s }",
                     i, quote(v.token()).c_str(), quote(v.lexeme()).c_str());
    }

    for (size_t i = tokens.size(); i < expects.size(); i++) {
      auto v = tokens[i];
      acutest_check_(false, file, line,
                     "erroneous missing token [%ld]: { token: %s, lexeme: %s }",
                     i, quote(v.token()).c_str(), quote(v.lexeme()).c_str());
    }
  }

  int loc = 0;
  bool res = procedure(tokens, loc);
  acutest_check_(res, file, line, "%s", "procedure");
}

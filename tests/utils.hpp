#pragma once

#include <algorithm>
#include <cassert>
#include <initializer_list>
#include <iomanip>
#include <map>
#include <optional>
#include <type_traits>
#include <vector>

#include "../lexer.hpp"
#include "../procedure_functions.h"

#include "../include/acutest.h"
#define macro TEST_NO_MAIN

#define TEST_EQUAL(a, b) test_equal_(a, b, __FILE__, __LINE__)

#define CURRENT_LOCATION __FILE__, __LINE__

static vector<token_323> parseTokens(std::string input) {
  // lexer_323 is hopelessly broken and does not treat EOF right. We can add a
  // whitespace to prevent EOF from being treated as an error.
  std::stringstream ss(input + "\n");
  std::vector<token_323> tokens;

  // Prevent lexer_323 from hanging indefinitely.
  int max = 200 + input.size();
  int i = 0;
  while (i < max) {
    auto token = lexer_323(ss);
    if (token.token() == "none") {
      break;
    }
    tokens.push_back(token);
    i++;
  }

  if (i == max) {
    throw std::runtime_error("lexer_323 is broken");
  }

  // Ignore the last few tokens, which are whitespaces or <none>s.
  while (
      (tokens.back().token() == "none" && tokens.back().lexeme() == "none") ||
      (tokens.back().token() == "Other Separators" &&
       tokens.back().lexeme() == "\n")) {
    tokens.pop_back();
  }

  return tokens;
}

static std::string quote(std::string s) {
  std::stringstream ss;
  ss << std::quoted(s);
  s = ss.str();

  std::string e(s);
  for (auto i = e.find('\n'); i != std::string::npos; i = e.find('\n')) {
    e.replace(i, 1, "\\n");
  }

  return e;
}

static std::string boolstr(bool v) { return v ? "true" : "false"; }

static void test_equal_(std::string a, std::string b, const char *file,
                        int line, const std::string what = "") {
  if (a == b) {
    acutest_check_(true, file, line, nullptr);
  } else {
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
  if (a == b) {
    acutest_check_(true, file, line, nullptr);
  } else {
    std::string err;
    if (what != "") {
      err = what + ": ";
    }
    if ((a & ~0b1) == 0 && (b & ~0b1) == 0) {
      // If both are 0 or 1, print them as bools.
      err += boolstr(a) + " != " + boolstr(b);
    } else {
      err += std::to_string(a) + " != " + std::to_string(b);
    }
    acutest_check_(false, file, line, "%s", err.c_str());
  }
}

struct ExpectToken {
  std::string token;
  std::string lexeme;
};

static void
test_impl(std::function<bool(std::vector<token_323> &, int &)> procedure,
          std::string input, std::initializer_list<ExpectToken> expectTokens,
          bool expectSuccess, std::optional<std::string> expectException,
          const char *file, int line) {

  TEST_CASE(quote(input).c_str());

  auto tokens = parseTokens(input);

  if (expectTokens.size() != 0) {
    test_equal_(tokens.size(), expectTokens.size(), file, line,
                "tokens.size mismatch");

    auto it = expectTokens.begin();
    for (size_t i = 0; i < min(tokens.size(), expectTokens.size()); i++) {
      test_equal_(tokens[i].token(), it->token, file, line,
                  "token [" + to_string(i) + "]: token mismatch");
      test_equal_(tokens[i].lexeme(), it->lexeme, file, line,
                  "token [" + to_string(i) + "]: lexeme mismatch");
      it++;
    }

    for (size_t i = expectTokens.size(); i < tokens.size(); i++) {
      auto v = tokens[i];
      acutest_check_(false, file, line, "erroneous extra token [%ld]: {%s, %s}",
                     i, quote(v.token()).c_str(), quote(v.lexeme()).c_str());
    }

    for (size_t i = tokens.size(); i < expectTokens.size(); i++) {
      auto v = tokens[i];
      acutest_check_(false, file, line,
                     "erroneous missing token [%ld]: {%s, %s}", i,
                     quote(v.token()).c_str(), quote(v.lexeme()).c_str());
    }
  }

  // Omit all space separators because no procedure functions like them.
  tokens.erase(std::remove_if(tokens.begin(), tokens.end(),
                              [](token_323 t) {
                                return t.token() == "Other Separators" &&
                                       t.lexeme() == " ";
                              }),
               tokens.end());

  int location = 0;
  try {
    bool res = procedure(tokens, location);
    test_equal_(res, expectSuccess, file, line, "procedure result mismatch");
  } catch (const std::logic_error &e) {
    if (expectSuccess) {
      std::stringstream msg;
      msg << "procedure: syntax error";
      if (location < tokens.size()) {
        msg << " "
            << "near token [" << location << "] "
            << "({" << std::quoted(tokens.at(location).token()) << ", "
            << std::quoted(tokens.at(location).lexeme()) << "})";
      } else if (location == tokens.size()) {
        msg << " at the end of the input";
      }
      acutest_check_(false, file, line, "%s: %s", msg.str().c_str(), e.what());
    } else {
      if (expectException != std::nullopt) {
        test_equal_(e.what(), expectException.value(), file, line,
                    "exception mismatch");
      }
      acutest_check_(true, file, line, "procedure: expected logic_error");
    }
  } catch (const std::exception &e) {
    acutest_check_(false, file, line, "procedure: unexpected exception: %s",
                   e.what());
  }
}

// test_pass tests that the given procedure function accepts the given input.
static void
test_pass(std::function<bool(std::vector<token_323> &, int &)> procedure,
          std::string input, std::initializer_list<ExpectToken> expectTokens,
          const char *file, int line) {

  test_impl(procedure, input, expectTokens, true, std::nullopt, file, line);
}

// test calls test_pass. It remains for backward compatibility.
const auto test = test_pass;

// test_fail tests that the given procedure function rejects the given input
// with the given exception.
static void
test_fail(std::function<bool(std::vector<token_323> &, int &)> procedure,
          std::string input, std::initializer_list<ExpectToken> expectTokens,
          std::optional<string> expectException, const char *file, int line) {

  test_impl(procedure, input, expectTokens, false, expectException, file, line);
}

// test_fail overloads the above test_fail without an expected exception.
static void
test_fail(std::function<bool(std::vector<token_323> &, int &)> procedure,
          std::string input, std::initializer_list<ExpectToken> expectTokens,
          const char *file, int line) {

  test_impl(procedure, input, expectTokens, false, std::nullopt, file, line);
}

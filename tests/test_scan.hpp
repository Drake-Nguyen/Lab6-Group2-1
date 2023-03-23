#include "../lexer.hpp"
#include "../procedure_functions.h"

#include "./utils.hpp"
#define macro TEST_NO_MAIN

#include <map>
#include <sstream>

static void test_scan(void) {

  test(procedureScan, "get(a);",
       {{"Function", "get"},
        {"Seperator", "("},
        {"Identifier", "a"},
        {"Seperator", ")"},
        {"Seperator", ";"}},
       CURRENT_LOCATION);
  test(procedureScan, "get(a,b);",
       {{"Function", "get"},
        {"Seperator", "("},
        {"Identifier", "a"},
        {"Seperator", ","},
        {"Identifier", "b"},
        {"Seperator", ")"},
        {"Seperator", ";"}},
       CURRENT_LOCATION);
  test(procedureScan, "get(a+b);",
       {{"Function", "get"},
        {"Seperator", "("},
        {"Identifier", "a"},
        {"Operator", "+"},
        {"Identifier", "b"},
        {"Seperator", ")"},
        {"Seperator", ";"}},
       CURRENT_LOCATION);

  test_fail(procedureScan, "get a;", {}, CURRENT_LOCATION);
  test_fail(procedureScan, "get a+b;", {}, CURRENT_LOCATION);
  test_fail(procedureScan, "get a,b;", {}, CURRENT_LOCATION);

}
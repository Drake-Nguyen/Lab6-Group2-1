#include "../lexer.hpp"
#include "../procedure_functions.h"

#include "./utils.hpp"
#define macro TEST_NO_MAIN

#include <map>
#include <sstream>

static void test_scan(void) {
<<<<<<< HEAD
  test(procedure_Scan, "get(a);",
       {{"Function", "get"},
        {"Seperator", "("},
        {"Identifier", "a"},
        {"Seperator", ")"},
        {"Seperator", ";"}},
       CURRENT_LOCATION);
  test(procedure_Scan, "get(a,b);",
       {{"Function", "get"},
        {"Seperator", "("},
        {"Identifier", "a"},
        {"Seperator", ","},
        {"Identifier", "b"},
        {"Seperator", ")"},
        {"Seperator", ";"}},
       CURRENT_LOCATION);
  test(procedure_Scan, "get(a+b);",
       {{"Function", "get"},
        {"Seperator", "("},
        {"Identifier", "a"},
        {"Operator", "+"},
        {"Identifier", "b"},
        {"Seperator", ")"},
        {"Seperator", ";"}},
       CURRENT_LOCATION);

  test_fail(procedure_Scan, "get a;", {}, CURRENT_LOCATION);
  test_fail(procedure_Scan, "get a+b;", {}, CURRENT_LOCATION);
  test_fail(procedure_Scan, "get a,b;", {}, CURRENT_LOCATION);

}
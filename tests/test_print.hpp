#include "../lexer.hpp"
#include "../procedure_functions.h"

#include "./utils.hpp"
#define macro TEST_NO_MAIN

#include <map>
#include <sstream>

static void test_print(void) {
test(procedureScan, "put(a);", {{"Function", "print"}, {"Seperator", "("}, 
{"Identifier", "a"}, {"Seperator", ")"}, {"Seperator", ";"}}, CURRENT_LOCATION);
test(procedureScan, "put(a,b);", {{"Function", "print"}, {"Seperator", "("}, 
{"Identifier", "a"}, {"Seperator", ","}, {"Identifier", "b"}, {"Seperator", ")"}, 
{"Seperator", ";"}}, CURRENT_LOCATION);
test(procedureScan, "put(a+b);", {{"Function", "print"}, {"Seperator", "("}, 
{"Identifier", "a"}, {"Operator", "+"}, {"Identifier", "b"}, {"Seperator", ")"}, 
{"Seperator", ";"}}, CURRENT_LOCATION);
  
test_fail(procedureScan, "put(a;", {}, CURRENT_LOCATION);
test_fail(procedureScan, "put a+b);", {}, CURRENT_LOCATION);
test_fail(procedureScan, "put a,b;", {}, CURRENT_LOCATION);
}
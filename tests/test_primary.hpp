#include "../lexer.hpp"
#include "../procedure_functions.h"

#include "./utils.hpp"
#define macro TEST_NO_MAIN

#include <map>
#include <sstream>

static void test_primary(void) {


  // test (procedurePrimary, "",{}, CURRENT_LOCATION);
  test(procedurePrimary, "temp", {{"Identifier", "temp"}}, CURRENT_LOCATION);
  test(procedurePrimary, "10", {{"Integer", "10"}}, CURRENT_LOCATION);
  test(procedurePrimary, "Temp integer",
       {{"Identifier", "Temp"},
        {"Other Separators", " "},
        {"Identifier", "integer"}},
       CURRENT_LOCATION);
  test(procedurePrimary, "temp+i",
       {{"Identifier", "temp"}, {"Operator", "+"}, {"Identifier", "i"}},
       CURRENT_LOCATION);
  test(procedurePrimary, "", {}, CURRENT_LOCATION);
  test(procedurePrimary, "3.14", {{"Real", "3.14"}}, CURRENT_LOCATION);
  test(procedurePrimary, "6.0222331231123146546",
       {{"Real", "6.0222331231123146546"}}, CURRENT_LOCATION);
  test(procedurePrimary, "1.0E-5", {{"Real", "1.0E-5"}}, CURRENT_LOCATION);
  test(procedurePrimary, "    ", {}, CURRENT_LOCATION);
  test(procedurePrimary, "true", {{"Keyword", "true"}}, CURRENT_LOCATION);
  test(procedurePrimary, "false", {{"Keyword", "false"}}, CURRENT_LOCATION);

}

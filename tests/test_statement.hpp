#include "../lexer.hpp"
#include "../procedure_functions.h"

#include "./utils.hpp"
#define macro TEST_NO_MAIN

#include <map>
#include <sstream>

static void test_statement(void) {
  test(procedure_Statement, "while(x==true)return;", {}, CURRENT_LOCATION);
  test(procedure_Statement, "if(x==y)return; fi", {}, CURRENT_LOCATION);
  test(procedure_If, "if(1==1){a=b;} fi", {}, CURRENT_LOCATION);
  test(procedure_If, "if(1==1)return; else return; fi", {}, CURRENT_LOCATION);
  test(procedure_Statement, "get(y);", {}, CURRENT_LOCATION);
  test(procedure_Statement, "put(x);", {}, CURRENT_LOCATION);
  test(procedure_Statement, "return;", {}, CURRENT_LOCATION);
  test(procedure_Statement, "return true;", {}, CURRENT_LOCATION);
  test(procedure_Statement, "x=y;", {}, CURRENT_LOCATION);
}

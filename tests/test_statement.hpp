#include "../lexer.hpp"
#include "../procedure_functions.h"

#include "./utils.hpp"
#define macro TEST_NO_MAIN

#include <map>
#include <sstream>

static void test_statement(void) {
  test(procedureStatement, "while(x==true)return;", {}, CURRENT_LOCATION);
  test(procedureStatement, "if(x==y)return; fi", {}, CURRENT_LOCATION);
  test(procedureIf, "if(1==1){a=b;} fi", {}, CURRENT_LOCATION);
  test(procedureIf, "if(1==1)return; else return; fi", {}, CURRENT_LOCATION);
  test(procedureStatement, "get(y);", {}, CURRENT_LOCATION);
  test(procedureStatement, "put(x);", {}, CURRENT_LOCATION);
  test(procedureStatement, "return;", {}, CURRENT_LOCATION);
  test(procedureStatement, "return true;", {}, CURRENT_LOCATION);
  test(procedureStatement, "x=y;", {}, CURRENT_LOCATION);
}

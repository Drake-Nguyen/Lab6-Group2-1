#include "../lexer.hpp"
#include "../procedure_functions.h"

#include "./utils.hpp"
#define macro TEST_NO_MAIN

#include <map>
#include <sstream>

static void test_while(void) {
  // valid assignment
  test(procedureWhile, "while(x==true)return;", {}, CURRENT_LOCATION);
  test(procedureWhile, "while (x!=10) return;", {}, CURRENT_LOCATION);
  test(procedureWhile, "while(x!=10)put(y);", {}, CURRENT_LOCATION);
  test(procedureWhile, "while(1>0)get(y);", {}, CURRENT_LOCATION);
  test(procedureWhile, "while(1==1)a=b;", {}, CURRENT_LOCATION);
  test(procedureWhile, "while(1==1)return false;", {}, CURRENT_LOCATION);
  test(procedureWhile, "while(1==1)while(1>0)return;", {}, CURRENT_LOCATION);
  test(procedureWhile, "while(1==1){x=y; return true;}", {}, CURRENT_LOCATION);
  test(procedureWhile, "while(1==1)if(x!=y)return; fi", {}, CURRENT_LOCATION);

  // invalid assignments
  test_fail(procedureWhile, "", {}, CURRENT_LOCATION);
  test_fail(procedureWhile, "while(", {}, CURRENT_LOCATION);
  test_fail(procedureWhile, "while(x)", {}, CURRENT_LOCATION);
  test_fail(procedureWhile, "while(x<)", {}, CURRENT_LOCATION);
  test_fail(procedureWhile, "while(x=123)", {}, CURRENT_LOCATION);
  test_fail(procedureWhile, "while(x>)", {}, CURRENT_LOCATION);
  test_fail(procedureWhile, "while(123<)", {}, CURRENT_LOCATION);
  test_fail(procedureWhile, "while(x!=456)return", {}, CURRENT_LOCATION);
  test_fail(procedureWhile, "while(x!=456)return0;", {}, CURRENT_LOCATION);
  test_fail(procedureWhile, "while(x!=456)", {}, CURRENT_LOCATION);
  test_fail(procedureWhile, "while(1==1||x==y)a=b;", {}, CURRENT_LOCATION);
}

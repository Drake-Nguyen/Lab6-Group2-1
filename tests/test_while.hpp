#include "../lexer.hpp"
#include "../procedure_functions.h"

#include "./utils.hpp"
#define macro TEST_NO_MAIN

#include <map>
#include <sstream>

static void test_while(void) {
  // valid assignment
  test(procedure_While, "while(x==true)return;", {}, CURRENT_LOCATION);
  test(procedure_While, "while (x!=10) return;", {}, CURRENT_LOCATION);
  test(procedure_While, "while(x!=10)put(y);", {}, CURRENT_LOCATION);
  test(procedure_While, "while(1>0)get(y);", {}, CURRENT_LOCATION);
  test(procedure_While, "while(1==1)a=b;", {}, CURRENT_LOCATION);
  test(procedure_While, "while(1==1)return false;", {}, CURRENT_LOCATION);
  test(procedure_While, "while(1==1)while(1>0)return;", {}, CURRENT_LOCATION);
  test(procedure_While, "while(1==1){x=y; return true;}", {}, CURRENT_LOCATION);
  test(procedure_While, "while(1==1)if(x!=y)return; fi", {}, CURRENT_LOCATION);



  // invalid assignments
  test_fail(procedure_While, "", {}, CURRENT_LOCATION);
  test_fail(procedure_While, "while(", {}, CURRENT_LOCATION);
  test_fail(procedure_While, "while(x)", {}, CURRENT_LOCATION);
  test_fail(procedure_While, "while(x<)", {}, CURRENT_LOCATION);
  test_fail(procedure_While, "while(x=123)", {}, CURRENT_LOCATION);
  test_fail(procedure_While, "while(x>)", {}, CURRENT_LOCATION);
  test_fail(procedure_While, "while(123<)", {}, CURRENT_LOCATION);
  test_fail(procedure_While, "while(x!=456)return", {}, CURRENT_LOCATION);
  test_fail(procedure_While, "while(x!=456)return0;", {}, CURRENT_LOCATION);
  test_fail(procedure_While, "while(x!=456)", {}, CURRENT_LOCATION);
  test_fail(procedure_While, "while(1==1||x==y)a=b;", {}, CURRENT_LOCATION);
}

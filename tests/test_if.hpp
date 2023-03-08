#include "../lexer.hpp"
#include "../procedure_functions.h"

#include "./utils.hpp"
#define macro TEST_NO_MAIN

#include <map>
#include <sstream>

static void test_if(void) {
  // no else

  // statement for compound
  test(procedure_If, "if(1==1){ return; } fi", {{}}, CURRENT_LOCATION);
  test(procedure_If, "if (1==1) { return; a = b; }", {}, CURRENT_LOCATION);
  test(procedure_If, "if (1==1) { a = b; }", {}, CURRENT_LOCATION);

  // statement for assign
  test(procedure_If, "if (1==1) a = b; fi", {}, CURRENT_LOCATION);

  // statement for (nested) if
  test(procedure_If, "if (1==1) if (false) a = b;", {}, CURRENT_LOCATION);
  test(procedure_If, "if (1==1) { if (false) return; }", {}, CURRENT_LOCATION);

  // statement for return
  test(procedure_If, "if (1==1) return;", {}, CURRENT_LOCATION);

  // statement for print
  test(procedure_If, "if (1==1) put('h');", {}, CURRENT_LOCATION);

  // statement for scan
  test(procedure_If, "if (1==1) get(a);", {}, CURRENT_LOCATION);

  // statement for while
  test(procedure_If, "if (1==1) while (false) a = b;", {}, CURRENT_LOCATION);

  // with else

  // statement for compound
  test(procedure_If, "if (1==1) { return; } else { return false; }", {},
       CURRENT_LOCATION);
  test(procedure_If, "if (1==1) { return; a = b; } else { return false; }", {},
       CURRENT_LOCATION);
  test(procedure_If, "if (1==1) { a = b; } else { return false; }", {},
       CURRENT_LOCATION);

  // statement for assign
  test(procedure_If, "if (1==1) a = b; else a = c;", {}, CURRENT_LOCATION);

  // statement for (nested) if
  test(procedure_If, "if (1==1) if (false) a = b; else a = c;", {},
       CURRENT_LOCATION);

  // statement for return
  test(procedure_If, "if (1==1) return; else return;", {}, CURRENT_LOCATION);

  // statement for print
  test(procedure_If, "if (1==1) put('h'); else put('e');", {},
       CURRENT_LOCATION);

  // statement for scan
  test(procedure_If, "if (1==1) get(a); else get(b);", {}, CURRENT_LOCATION);

  // statement for while
  test(procedure_If, "if (1==1) while (false) a = b; else while (false) a = c;",
       {}, CURRENT_LOCATION);
}

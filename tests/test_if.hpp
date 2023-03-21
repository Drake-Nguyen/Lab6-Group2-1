#include "../lexer.hpp"
#include "../procedure_functions.h"

#include "./utils.hpp"
#define macro TEST_NO_MAIN

#include <map>
#include <sstream>

static void test_if(void) {
  // no else

  // statement for compound
  test(procedureIf, "if (1 == 1) { return; } fi", {}, CURRENT_LOCATION);
  test(procedureIf, "if (1 == 1) { return; a = b; } fi", {}, CURRENT_LOCATION);
  test(procedureIf, "if (1 == 1) { a = b; } fi", {}, CURRENT_LOCATION);

  // statement for assign
  test(procedureIf, "if (1 == 1) a = b; fi", {}, CURRENT_LOCATION);

  // statement for (nested) if
  test(procedureIf, "if (1 == 1) if (0 == 1) a = b; fi fi", {},
       CURRENT_LOCATION);
  test(procedureIf, "if (1 == 1) { if (0 == 1) return; fi } fi", {},
       CURRENT_LOCATION);

  // statement for return
  test(procedureIf, "if (1 == 1) return; fi", {}, CURRENT_LOCATION);

  // statement for print
  test(procedureIf, "if (1 == 1) put(h); fi", {}, CURRENT_LOCATION);

  // statement for scan
  test(procedureIf, "if (1 == 1) get(a); fi", {}, CURRENT_LOCATION);

  // statement for while
  test(procedureIf, "if (1 == 1) while (0 == 1) a = b; fi", {},
       CURRENT_LOCATION);

  // with else

  // statement for compound
  test(procedureIf, "if (1 == 1) { return; } else { return false; } fi", {},
       CURRENT_LOCATION);
  test(procedureIf, "if (1 == 1) { return; a = b; } else { return false; } fi",
       {}, CURRENT_LOCATION);
  test(procedureIf, "if (1 == 1) { a = b; } else { return false; } fi", {},
       CURRENT_LOCATION);

  // statement for assign
  test(procedureIf, "if (1 == 1) a = b; else a = c; fi", {}, CURRENT_LOCATION);

  // statement for (nested) if
  test(procedureIf, "if (1 == 1) if (0 == 1) a = b; else a = c; fi fi", {},
       CURRENT_LOCATION);

  // statement for return
  test(procedureIf, "if (1 == 1) return; else return; fi", {},
       CURRENT_LOCATION);

  // statement for print
  test(procedureIf, "if (1 == 1) put(h); else put(e); fi", {},
       CURRENT_LOCATION);

  // statement for scan
  test(procedureIf, "if (1 == 1) get(a); else get(b); fi", {},
       CURRENT_LOCATION);

  // statement for while
  test(procedureIf,
       "if (1 == 1) while (0 == 1) a = b; else while (1 == 1) a = c; fi", {},
       CURRENT_LOCATION);
}

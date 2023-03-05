#include "../lexer.hpp"
#include "../procedure_functions.h"

#include "./utils.hpp"
#define macro TEST_NO_MAIN

#include <map>
#include <sstream>

static void test_id (void) {

   // test (procedure_IDs, "",{}, CURRENT_LOCATION);
   test (procedure_IDs, "a", {{"Identifier", "a"}}, CURRENT_LOCATION);
   test (procedure_IDs, "a,b", {{"Identifier", "a"}, {"Separator", ","}, {"Identifier", "b"}}, CURRENT_LOCATION);
   test (procedure_IDs, "a+B", {{"Identifier", "a"}, {"Operator", "+"}, {"Identifier", "B"}}, CURRENT_LOCATION);
   test (procedure_IDs, "class", {{"Keyword", "class"}}, CURRENT_LOCATION);
   test (procedure_IDs, "", {}, CURRENT_LOCATION);
   test (procedure_IDs, "a b", {{"Identifier", "a"}, {"Other Separators", " "}, {"Identifier", "b"}}, CURRENT_LOCATION);
   test (procedure_IDs, "    ", {}, CURRENT_LOCATION);
   test (procedure_IDs, "$tring", {{"Identifier", "$tring"}}, CURRENT_LOCATION);
   
}

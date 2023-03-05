#include "../lexer.hpp"
#include "../procedure_functions.h"

#include "./utils.hpp"
#define macro TEST_NO_MAIN

#include <map>
#include <sstream>

static void test_primary(void)
{

    // test (procedure_Primary, "",{}, CURRENT_LOCATION);
    test(procedure_Primary, "a", {{"Identifier", "a"}}, CURRENT_LOCATION);
    test(procedure_Primary, "a,b", {{"Identifier", "a"}, {"Separator", ","}, {"Identifier", "b"}}, CURRENT_LOCATION);
    test(procedure_Primary, "a+B", {{"Identifier", "a"}, {"Operator", "+"}, {"Identifier", "B"}}, CURRENT_LOCATION);
    test(procedure_Primary, "class", {{"Keyword", "class"}}, CURRENT_LOCATION);
    test(procedure_Primary, "", {}, CURRENT_LOCATION);
    test(procedure_Primary, "a b", {{"Identifier", "a"}, {"Other Separators", " "}, {"Identifier", "b"}}, CURRENT_LOCATION);
    test(procedure_Primary, "    ", {}, CURRENT_LOCATION);
    test(procedure_Primary, "$tring", {{"Identifier", "$tring"}}, CURRENT_LOCATION);
}

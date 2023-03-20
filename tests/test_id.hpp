#include "../lexer.hpp"
#include "../procedure_functions.h"

#include "./utils.hpp"
#define macro TEST_NO_MAIN

#include <map>
#include <sstream>




static void test_id (void) {
   
   procedureIDs ids;

   // test (procedure_IDs, "",{}, CURRENT_LOCATION);
   
   test ([&ids](std::vector<token_323>& tokens, int& index) {return ids.procedure_IDs(tokens, index);}, "a", {{"Identifier", "a"}}, CURRENT_LOCATION);
   test ([&ids](std::vector<token_323>& tokens, int& index) {return ids.procedure_IDs(tokens, index);}, "apple,banana", {{"Identifier", "apple"}, {"Separator", ","}, {"Identifier", "banana"}}, CURRENT_LOCATION);
   test ([&ids](std::vector<token_323>& tokens, int& index) {return ids.procedure_IDs(tokens, index);}, "a+B", {{"Identifier", "a"}, {"Operator", "+"}, {"Identifier", "B"}}, CURRENT_LOCATION);
   test ([&ids](std::vector<token_323>& tokens, int& index) {return ids.procedure_IDs(tokens, index);}, "a b", {{"Identifier", "a"}, {"Other Separators", " "}, {"Identifier", "b"}}, CURRENT_LOCATION);
   
   //test_fail (procedure_IDs::procedure_IDs, &testID, "    ", {}, CURRENT_LOCATION);
   //test_fail (procedure_IDs::procedure_IDs, &testID, "class", {{"Keyword", "class"}}, CURRENT_LOCATION);
   //test_fail (procedure_IDs::procedure_IDs, &testID, "", {}, CURRENT_LOCATION);
   //test_fail (procedure_IDs, "$tring", {{"Identifier", "$tring"}}, CURRENT_LOCATION);
   
}

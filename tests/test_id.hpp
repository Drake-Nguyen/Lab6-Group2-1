#include "../lexer.hpp"
#include "../procedure_functions.h"

#include "./utils.hpp"
#define macro TEST_NO_MAIN

#include <map>
#include <sstream>

static void test_id (void) {
   
   //procedureIDs ids;

   // test (procedureIDs, "",{}, CURRENT_LOCATION);

   test (procedureIDs, "a", {{"Identifier", "a"}}, CURRENT_LOCATION);
   test (procedureIDs, "apple,banana", {{"Identifier", "apple"}, {"Separator", ","}, {"Identifier", "banana"}}, CURRENT_LOCATION);
   test (procedureIDs, "a+B", {{"Identifier", "a"}, {"Operator", "+"}, {"Identifier", "B"}}, CURRENT_LOCATION);
   test (procedureIDs, "a b", {{"Identifier", "a"}, {"Other Separators", " "}, {"Identifier", "b"}}, CURRENT_LOCATION);
    
   test_fail (procedureIDs, "    ", {}, CURRENT_LOCATION);
   test_fail (procedureIDs, "class", {{"Keyword", "class"}}, CURRENT_LOCATION);
   test_fail (procedureIDs, "", {}, CURRENT_LOCATION);

   // test ([&ids](std::vector<token_323>& tokens, int& index) {return ids.procedureIDs(tokens, index);}, "a", {{"Identifier", "a"}}, CURRENT_LOCATION);
   // test ([&ids](std::vector<token_323>& tokens, int& index) {return ids.procedureIDs(tokens, index);}, "apple,banana", {{"Identifier", "apple"}, {"Separator", ","}, {"Identifier", "banana"}}, CURRENT_LOCATION);
   // test ([&ids](std::vector<token_323>& tokens, int& index) {return ids.procedureIDs(tokens, index);}, "a+B", {{"Identifier", "a"}, {"Operator", "+"}, {"Identifier", "B"}}, CURRENT_LOCATION);
   // test ([&ids](std::vector<token_323>& tokens, int& index) {return ids.procedureIDs(tokens, index);}, "a b", {{"Identifier", "a"}, {"Other Separators", " "}, {"Identifier", "b"}}, CURRENT_LOCATION);
   
   // test_fail ([&ids](std::vector<token_323>& tokens, int& index) {return ids.procedureIDs(tokens, index);}, "    ", {}, CURRENT_LOCATION);
   // test_fail ([&ids](std::vector<token_323>& tokens, int& index) {return ids.procedureIDs(tokens, index);}, "class", {{"Keyword", "class"}}, CURRENT_LOCATION);
   // test_fail ([&ids](std::vector<token_323>& tokens, int& index) {return ids.procedureIDs(tokens, index);}, "", {}, CURRENT_LOCATION);

   //test_fail (procedureIDs, "$tring", {{"Identifier", "$tring"}}, CURRENT_LOCATION);
   
}
